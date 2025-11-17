/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AParser.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:35:12 by luide-ca          #+#    #+#             */
/*   Updated: 2025/11/17 18:03:12 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APARSER_HPP
# define APARSER_HPP

# include <iostream>

class AParser {
    protected:
                // receives the buffer and length corresponding to the item we are parsing
                std::string _buffer;
                std::string _limiter;
                
    public:
                // orthodox-canonical form methods
                AParser(void);
                AParser(const std::string buffer, const std::string limiter);
                AParser(const AParser& other);
                AParser& operator=(const AParser& other);

                virtual ~AParser(void);

                void getBuffer(void);
                void getLimiter(void);
};

#endif