/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:26:00 by luide-ca          #+#    #+#             */
/*   Updated: 2025/11/25 15:33:03 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_HPP
# define HTTP_REQUEST_HPP

# include <string>
# include <map>
# include <exception>

class HTTPRequest
{
    private:
        // ===== Raw data =====
        std::string _raw;

        // ===== Request line =====
        std::string _method;
        std::string _path;
        std::string _httpVersion;

        // ===== Headers + body =====
        std::map<std::string, std::string> _headers;
        std::string                        _body;

        // ===== Internal helpers =====
        bool isValidPath(const std::string &path) const;
        
        bool isValidChunkedBody(const std::string &body) const;
        bool isValidBody(const std::string &body) const;

        // ===== Internal Parsers =====
        void parseRequestLine(const std::string &line);
        void parseHeadersBlock(const std::string &block);
        void parseBody(const std::string &body);

        void setMethod(const std::string &method);
        void setPath(const std::string &path);
        void setHTTPVersion(const std::string &version);

    public:
        // ===== Canonical form =====
        HTTPRequest();
        explicit HTTPRequest(int fd);                // read + parse from fd
        HTTPRequest(const HTTPRequest &other);
        HTTPRequest &operator=(const HTTPRequest &other);
        ~HTTPRequest();

        // ===== Public API =====
        void        readFromFd(int fd);              // only read from socket into _raw
        void        parse();                         // parse _raw into components

        const std::string &getRaw() const;
        const std::string &getMethod() const;
        const std::string &getPath() const;
        const std::string &getHTTPVersion() const;
        const std::map<std::string, std::string> &getHeaders() const;
        std::string        getHeader(const std::string &key) const;
        const std::string &getBody() const;

        // ===== Exceptions =====
        class MethodException : public std::exception {
        public:
            virtual const char *what() const throw();
        };

        class PathException : public std::exception {
        public:
            virtual const char *what() const throw();
        };

        class HTTPVersionException : public std::exception {
        public:
            virtual const char *what() const throw();
        };

        class HeaderException : public std::exception {
        public:
            virtual const char *what() const throw();
        };

        class BodyException : public std::exception {
        public:
            virtual const char *what() const throw();
        };

        class ParseException : public std::exception {
        public:
            ParseException(const std::string &msg);
            ParseException(const ParseException &other);
            ParseException &operator=(const ParseException &other);
            virtual ~ParseException() throw();
            virtual const char *what() const throw();
        private:
            std::string _msg;
        };
};

std::string toLower(const std::string &s);

#endif // HTTP_REQUEST_HPP
