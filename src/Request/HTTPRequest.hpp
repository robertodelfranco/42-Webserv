/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luide-ca <luide-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 09:58:08 by luide-ca          #+#    #+#             */
/*   Updated: 2025/11/17 18:02:32 by luide-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_HPP
# define HTTP_REQUEST_HPP

# include <iostream>
# include <exception>

class HTTPRequest {
	private:
			// receives full buffer and full length from recv call
			std::string _buffer;
			int _lengthBuffer;

	public:
			// orthodox-canonical form
			HTTPRequest(void);
			HTTPRequest(const std::string buffer, int lengthBuffer);
			HTTPRequest(const HTTPRequest& other);
			~HTTPRequest( /*feel with everything necessary*/ );
			
			HTTPRequest& operator=( const HTTPRequest& other );

			// specfic methods
			void getBuffer(void) const;
			int getLengthBuffer(void) const;
};

#endif