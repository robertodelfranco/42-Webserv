/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_new_idea.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:26:00 by luide-ca          #+#    #+#             */
/*   Updated: 2025/11/24 17:26:02 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_HPP
# define HTTP_REQUEST_HPP

# include <string>
# include <map>
# include <exception>

class HTTPRequest {
    private:
        // raw input
        std::string _buffer;
        std::size_t _lengthBuffer;

        // request line
        std::string _method;
        std::string _path;
        std::string _httpVersion;

        // headers
        std::map<std::string, std::string> _headers;

        // body
        std::string _body;

    public:
        /*
        ========== Orthodox Canonical Form
        */
        HTTPRequest();
        HTTPRequest(const std::string &buffer, std::size_t lengthBuffer);
        HTTPRequest(const HTTPRequest &other);
        HTTPRequest &operator=(const HTTPRequest &other);
        ~HTTPRequest();

        /*
        ========== Access to raw buffer info
        */
        const std::string &getFullBuffer() const;
        std::size_t        getFullLengthBuffer() const;

        /*
        ========== Request line
        */
        const std::string &getMethod() const;
        const std::string &getPath() const;
        const std::string &getHTTPVersion() const;

        void setMethod(const std::string &method);
        void setPath(const std::string &path);
        void setHTTPVersion(const std::string &version);

        /*
        ========== Headers
        */
        const std::map<std::string, std::string> &getHeaders() const;
        std::string                               getHeader(const std::string &key) const;
        void                                      addHeader(const std::string &key,
                                                           const std::string &value);

        /*
        ========== Body
        */
        const std::string &getBody() const;
        void               setBody(const std::string &body);

        /*
        ========== Parsing interface
        */
        void parseRequestLine(const std::string &buffer);
        void parseHeaderLine(const std::string &buffer);
        void parseBody(const std::string &buffer);

        /*
        ========== Exceptions
        */
        class InputException : public std::exception {
        public:
            virtual const char* what() const throw();
        };

        class MethodException : public std::exception {
        public:
            virtual const char* what() const throw();
        };

        class PathException : public std::exception {
        public:
            virtual const char* what() const throw();
        };

        class HTTPTypeException : public std::exception {
        public:
            virtual const char* what() const throw();
        };

        class RequestEndLineException : public std::exception {
        public:
            virtual const char* what() const throw();
        };

        class KeyHeaderException : public std::exception {
        public:
            virtual const char* what() const throw();
        };

        class ValueHeaderException : public std::exception {
        public:
            virtual const char* what() const throw();
        };

        class HeaderEndException : public std::exception {
        public:
            virtual const char* what() const throw();
        };

        class BodyException : public std::exception {
        public:
            virtual const char* what() const throw();
        };
};

#endif
