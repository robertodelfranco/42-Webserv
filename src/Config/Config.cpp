#include "Config.hpp"

Config::Config() : servers() {}

Config::Config(const Config& other) : servers(other.servers) {}

Config& Config::operator=(const Config& other) {
	if (this != &other) {
		servers = other.servers;
	}
	return *this;
}

Config::~Config() {}

Config::ParseError::ParseError(const std::string& msg, size_t line, size_t col, const std::string& snippet) {
	std::ostringstream	os;

	os << "Parse error: " << msg << " (line: " << line << " col: " << col + 1 << ")";
	if (!snippet.empty())
		os << "\n" << snippet << "\n" << std::string(col, ' ') << '^';

	m_message = os.str();
};

const char*	Config::ParseError::what() const throw() {
	return m_message.c_str();
}

void	Config::init(const char *file) {
	if (!file || !*file) {
		std::cerr << "Nenhum arquivo de configuração foi encontrado" << std::endl;
		return;
	}

	std::ifstream	configFile(file);
	
	if (!configFile) {
		std::cerr << "Erro ao abrir o arquivo de configuração: " << file << std::endl;
		return;
	}

	std::string line;
	size_t	count_lines = 1;
	while (std::getline(configFile, line)) {
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
	configFile.close();
}

static bool	is_identifier_char(unsigned char c) {
	if (std::isalpha(c)) return true;
	if (std::isdigit(c)) return true;
	if (c == '_') return true;

	return false;
}

size_t	Config::consumeIdentifier(const std::string& line, size_t count_line, size_t col) {
	if (col >= line.size())
		return col;

	unsigned char	c = static_cast<unsigned char>(line[col]);
	size_t		start = col;

	if (!is_identifier_char(c))
		return col;
	++col;
	
	while (col < line.size()) {
		c = static_cast<unsigned char>(line[col]);
		
		if (Utils::has_char(" {;}", c))
			break ;
		
		if (!is_identifier_char(c))
			break ;
		
		++col;
	}

	if (col == start)
		return col;
	
	tokens.push_back(Token(IDENTIFIER, line.substr(start, col - start), count_line, start));
	
	return col;
}

size_t	Config::consumeNumber(const std::string& line, size_t count_line, size_t col) {
	if (col >= line.size())
		return col;

	unsigned char	c = static_cast<unsigned char>(line[col]);
	size_t		start = col;

	if (!std::isdigit(c))
		throw ParseError("Unexpected char after number sequence", count_line, col, line);
	++col;

	while (col < line.size()) {
		c = static_cast<unsigned char>(line[col]);

		if (Utils::has_char(" {;}", c))
			break ;
		
		if (!std::isdigit(c))
			throw ParseError("Unexpected char after number sequence", count_line, col, line);

		++col;
	}

	tokens.push_back(Token(NUMBER, line.substr(start, col - start), count_line, start));

	return col;
}

size_t	Config::consumeString(const std::string& line, size_t count_line, size_t col) {
	(void)line;
	(void)col;
	(void)count_line;
	return 1;
}

size_t	Config::consumePath(const std::string& line, size_t count_line, size_t col) {
	(void)line;
	(void)col;
	(void)count_line;
	return 1;
}

size_t	Config::consumeSymbol(const std::string& line, size_t count_line, size_t col) {
	(void)line;
	(void)col;
	(void)count_line;
	return 1;
}

size_t	Config::edgeCases(const std::string& line, size_t count_line, size_t col) {
	(void)line;
	(void)col;
	(void)count_line;
	return 1;
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
			col = consumeIdentifier(line, count_line, col);
		else if (std::isdigit(c))
			col = consumeNumber(line, count_line, col);
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
