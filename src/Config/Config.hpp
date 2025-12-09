#ifndef CONFIG_HPP
# define CONFIG_HPP

#include "../Utils/Utils.hpp"
#include "Server.hpp"

class Config {
	private:
		typedef void (Config::*TokenHandler)(std::vector<Token>::iterator); // protótipo para declarar array de funções
		// HttpConfig			global_config; // classe que reune todos os dados do arquivo config
		std::vector<Server>	servers; // blocos de servidores que reunem todos os dados do arquivo config
		std::ifstream		config_file;
		std::vector<Token>	tokens;
		std::map<std::string, TokenHandler>	handlers;

		// Parser
		std::vector<Token>::iterator&	getServerBlock(std::vector<Token>::iterator it);
		std::vector<Token>::iterator&	consumeDirective(std::vector<Token>::iterator it);
		void							getListen(std::vector<Token>::iterator it);
		void							getServerName(std::vector<Token>::iterator it);
		void							getBodySize(std::vector<Token>::iterator it);
		void							getRoot(std::vector<Token>::iterator it);
		void							getIndexPage(std::vector<Token>::iterator it);
		void							getErrorPages(std::vector<Token>::iterator it);
		void							getMethods(std::vector<Token>::iterator it);
		void							getRedirect(std::vector<Token>::iterator it);
		void							getCgi(std::vector<Token>::iterator it);
		
		// Lexer
		void							consumeLine(std::string& line, size_t count_line);
		size_t							consumeDirective(const std::string& line, size_t count_line, size_t col);
		size_t							consumeName(const std::string& line, size_t count_line, size_t col);
		size_t							consumeString(const std::string& line, size_t count_line, size_t col);
		size_t							consumePath(const std::string& line, size_t count_line, size_t col);
		size_t							consumeSymbol(const std::string& line, size_t count_line, size_t col);
		size_t							edgeCase(const std::string& line, size_t count_line, size_t col);

	public:
		Config();
		Config(const Config& other);
		Config& operator=(const Config& other);
		~Config();

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