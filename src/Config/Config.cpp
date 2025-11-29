#include "Config.hpp"

Config::Config() : global_config() {}

Config::Config(const Config& other) : global_config(other.global_config) {}

Config& Config::operator=(const Config& other) {
	if (this != &other) {
		global_config = other.global_config;
	}
	return *this;
}

Config::~Config() {}

Config::ParseError::ParseError(const std::string& msg, size_t line, size_t col, const std::string& snippet) {
	std::ostringstream	os;

	os << "Parse error: " << msg << " (line: " << line << " col: " << col + 1 << ")";
	if (!snippet.empty())
		os << "\n" << snippet << "\n" << RED << std::string(col, ' ') << '^' << RESET;

	m_message = os.str();
};

const char*	Config::ParseError::what() const throw() {
	return m_message.c_str();
}

static bool	is_directive_char(unsigned char c) {
	if (std::isalpha(c)) return true;
	if (std::isdigit(c)) return true;
	if (c == '_') return true;

	return false;
}

size_t	Config::consumeDirective(const std::string& line, size_t count_line, size_t col) {
	if (col >= line.size())
		return col;

	unsigned char	c = static_cast<unsigned char>(line[col]);
	size_t		start = col;

	if (!is_directive_char(c))
		return col;
	++col;
	
	while (col < line.size()) {
		c = static_cast<unsigned char>(line[col]);
		
		if (Utils::has_char(" \t{;}", c))
			break ;
		
		if (!is_directive_char(c))
			break ;
		
		++col;
	}

	if (col == start)
		return col;
	
	tokens.push_back(Token(DIRECTIVE, line.substr(start, col - start), count_line, start + 1));
	
	return col;
}

size_t	Config::consumeName(const std::string& line, size_t count_line, size_t col) {
	if (col >= line.size())
		return col;

	size_t		start = col;

	while (col < line.size()) {
		unsigned char	c = static_cast<unsigned char>(line[col]);

		if (Utils::has_char(" \t{;}", c))
			break ;
	
		if (c == '\'' || c == '"')
			throw ParseError("Invalid quotes in name", count_line, col, line);
		
		if (c == '\0' && c < 32)
			throw ParseError("Unexpected control character in name", count_line, col, line);

		++col;
	}

	tokens.push_back(Token(NAME, line.substr(start, col - start), count_line, start));
	
	return col;
}

size_t	Config::consumeString(const std::string& line, size_t count_line, size_t col) {
	if (col >= line.size())
		return col;

	unsigned char	quote = static_cast<unsigned char>(line[col]);
	if (quote != '"' && quote != '\'')
		return col;
	
	size_t		start = col;
	++col;
	
	std::string content;
	while (col < line.size()) {
		unsigned char	c = static_cast<unsigned char>(line[col]);

		if (c == '\\') {
			++col;
			if (col >= line.size())
				throw ParseError("Invalid escape at the end of line", count_line, col, line);
			content.push_back(line[col]);
			++col;
			continue ;
		}

		if (c == quote) {
			++col;
			
			if (content.empty())
				throw ParseError("Empty string", count_line, col, line);

			tokens.push_back(Token(STRING, content, count_line, start + 1));
			return col;
		}
		content.push_back(line[col]);
		++col;
	}

	throw ParseError("Unclosed quotes", count_line, col, line);
}

size_t	Config::consumePath(const std::string& line, size_t count_line, size_t col) {
	if (col >= line.size())
		return col;

	unsigned char	c = static_cast<unsigned char>(line[col]);
	size_t		start = col;

	if (Utils::has_char(" \t{;}", c))
		return col;
	++col;

	while (col < line.size()) {
		c = static_cast<unsigned char>(line[col]);

		if (Utils::has_char(" \t{;}", c))
			break ;
		
		if (c == '\'' || c == '"')
			throw ParseError("Invalid quotes in path", count_line, col, line);

		if (c == '\0' || c < 32)
			throw ParseError("Unexpected control character in path", count_line, col, line);

		++col;
	}

	tokens.push_back(Token(PATH, line.substr(start, col - start), count_line, start + 1));

	return col;
}

size_t	Config::consumeSymbol(const std::string& line, size_t count_line, size_t col) {
	if (col >= line.size())
		return col;

	unsigned char	c = static_cast<unsigned char>(line[col]);
	size_t		start =	col;

	if (!Utils::has_char("{;}", c))
		return col;
	++col;

	TokenType type;

	if (c == '{') type = LBRACE;
	else if (c == '}') type = RBRACE;
	else type = SEMICOLON;

	tokens.push_back(Token(type, line.substr(start, col - start), count_line, start + 1));

	return col;
}

size_t	Config::edgeCases(const std::string& line, size_t count_line, size_t col) {
	(void)line;
	(void)col;
	(void)count_line;
	std::cout << CYAN << "Edge case" << RESET << std::endl;
	return col + 1;
}

void	Config::consumeLine(std::string& line, size_t count_line) {

	if (line.empty())
		return ;

	size_t	col = 0;
	while (col < line.size()) {
		unsigned char c = static_cast<unsigned char>(line[col]);

		if (std::isspace(c)) {
			++col;
			continue ;
		}
		if (col == 0 && (std::isalpha(c) || c == '_'))
			col = consumeDirective(line, count_line, col);
		else if (std::isalpha(c) || c == '_' || std::isdigit(c))
			col = consumeName(line, count_line, col);
		else if (c == '\"' || c == '\'')
			col = consumeString(line, count_line, col);
		else if (c == '/' || c == '.')
			col = consumePath(line, count_line, col);
		else if (c == '{' || c == '}' || c == ';')
			col = consumeSymbol(line, count_line, col);
		else
			col = edgeCases(line, count_line, col);
	}
}

void	Config::init(const char *file) {
	if (!file || !*file) {
		std::cerr << "Nenhum arquivo de configuração foi encontrado" << std::endl;
		return;
	}

	std::ifstream	config_file(file);
	
	if (!config_file) {
		std::cerr << "Erro ao abrir o arquivo de configuração: " << file << std::endl;
		return;
	}

	std::string line;
	size_t	count_lines = 1;
	while (std::getline(config_file, line)) {
		size_t pos = line.find('#');
		if (pos != std::string::npos) {
			line = line.substr(0, pos);
		}
		Utils::ref_trim(line);
		if (line.length() > 0) {
			std::cout << YELLOW << line << " |" << RESET << std::endl;
			consumeLine(line, count_lines);
		}
		++count_lines;
	}
	tokens.push_back(Token(END_OF_STREAM, "EOF", count_lines, 0));
	config_file.close();

	std::cout << std::endl;
	for (std::vector<Token>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
		std::cout << GREEN << it->type << " -- " << it->value << "\n" << it->line << " -- " << it->col << RESET << std::endl;
		std::cout << std::endl;
	}
}
