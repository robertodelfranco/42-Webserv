/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:26:36 by luide-ca          #+#    #+#             */
/*   Updated: 2025/11/24 19:07:47 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPRequest.hpp"

const std::string &HTTPRequest::getFullBuffer(int fd) const {
    std::string acc;
    
    while (true) {
        char temp[1024];
        ssize_t n = recv(fd, temp, sizeof(temp), 0);
    
        if (n <= 0) break;
    
        acc.append(temp, n);
    }
    return (acc);
}

void HTTPRequest::setRequestLine(const std::string &buffer) {
    size_t delimiter_rl;

    while (delimiter_rl = buffer.find_first_of('/r/n') != std::string::npos) {
        this->_requestLine = buffer.substr(0, delimiter_rl);
    }
}

void HTTPRequest::setHeader(const std::string &buffer) {
    size_t delimiter_rl;
    size_t delimiter_header;

    while (delimiter_rl = buffer.find_first_of('/r/n') != std::string::npos) {
        while (delimiter_header = buffer.find('/r/n/r/n') != std::string::npos) {
            this->_header = buffer.substr(delimiter_rl + 2, delimiter_header);
        }
    }
}

void HTTPRequest::setBody(const std::string &buffer) {
    size_t delimiter_header;
    
    while (delimiter_header = buffer.find('/r/n/r/n') != std::string::npos) {
        this->_body = buffer.substr(delimiter_header + 4, this->_lengthBuffer);
    }
}