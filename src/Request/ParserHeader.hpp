/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserHeader.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:19:46 by luide-ca          #+#    #+#             */
/*   Updated: 2025/11/17 18:25:41 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HEADER_HPP
# define PARSER_HEADER_HPP

# include "AParser.hpp"

class ParserHeader : public AParser {
    private:
                std::string _key;
                std::string _value;

    public:
                // orthodox-canonical form methods
                ParserHeader(void);
                ParserHeader(const std::string buffer, const std::string limiter);
                ParserHeader(const ParserHeader& other);
                ParserHeader& operator=(const ParserHeader& other);

                virtual ~ParserHeader(void);

                // getters
                std::string getKey(void);
                std::string getValue(void);

                // setter
                std::string setKey(std::string key);
                std::string setValue(std::string value);

                // parsing buffer
                void parserKey(const std::string buffer);
                void parserValue(const std::string buffer);
};

#endif