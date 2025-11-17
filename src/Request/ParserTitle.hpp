/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserTitle.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:52:18 by luide-ca          #+#    #+#             */
/*   Updated: 2025/11/17 18:10:54 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_TITLE_HPP
# define PARSER_TITLE_HPP

# include <iostream>
# include "AParser.hpp"

class ParserTitle : public AParser {
    private:
                std::string _method;
                std::string _path;
                std::string _httpType;

    public:
                // orthodox-canonical form methods
                ParserTitle(void);
                ParserTitle(const std::string buffer, const std::string limiter);
                ParserTitle(const ParserTitle& other);
                ParserTitle& operator=(const ParserTitle& other);

                virtual ~ParserTitle(void);

                // getters
                std::string getMethod(void);
                std::string getPath(void);
                std::string getHTTPType(void);

                // setters
                std::string setMethod(std::string method);
                std::string setPath(std::string path);
                std::string setHTTPType(std::string httpType);

                // parsing buffer
                void parserMethod(const std::string buffer);
                void parserPath(const std::string buffer);
                void parserHTTPType(const std::string buffer);
};

#endif;