#ifndef CONFIG_HPP
# define CONFIG_HPP

#include "../Utils/Utils.hpp"
#include "HttpConfig.hpp"

class Config {
	private:
		HttpConfig			global_config; // classe que reune todos os dados do arquivo config
		std::ifstream		config_file;
		std::vector<Token>	tokens;

		// Parser
		void	consumeToken(std::vector<Token>::iterator it);
		void	getUnknown(std::vector<Token>::iterator it);
		void	getDirective(std::vector<Token>::iterator it);
		void	getString(std::vector<Token>::iterator it);
		void	getPath(std::vector<Token>::iterator it);
		void	getSymbol(std::vector<Token>::iterator it);
		void	getEdgeCase(std::vector<Token>::iterator it);
		
		// Lexer
		void	consumeLine(std::string& line, size_t count_line);
		size_t	consumeDirective(const std::string& line, size_t count_line, size_t col);
		size_t	consumeName(const std::string& line, size_t count_line, size_t col);
		size_t	consumeString(const std::string& line, size_t count_line, size_t col);
		size_t	consumePath(const std::string& line, size_t count_line, size_t col);
		size_t	consumeSymbol(const std::string& line, size_t count_line, size_t col);
		size_t	edgeCase(const std::string& line, size_t count_line, size_t col);

	public:
		Config();
		Config(const Config& other);
		Config& operator=(const Config& other);
		~Config();

		typedef void (Config::*TokenHandler)(std::vector<Token>::iterator); // protótipo para declarar array de funções

		class ParseError : public std::exception {
			private:
				std::string	m_message;
			public:
				ParseError(const std::string& msg, size_t line, size_t col, const std::string& snippet);
				virtual ~ParseError() throw() {};
				const char* what() const throw();
		};

		void	initLexer(const char *file);
		void	initParser();
};

#endif