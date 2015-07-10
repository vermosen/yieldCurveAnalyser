/*
 * tcpClient.hpp
 *
 *  Created on: May 22, 2015
 *      Author: vermosen
 */

#ifndef TCPCLIENT_HPP_
#define TCPCLIENT_HPP_

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>

#include <shared/tcpConnection/tcpConnection.hpp>
#include <shared/sqlLogin/sqlLogin.hpp>
#include <shared/message/message.hpp>
#include <client/mainWindow/scrolledLogWindow/scrolledLogWindow.hpp>

class tcpClient : public boost::enable_shared_from_this<tcpClient> {

public:

	static boost::shared_ptr<tcpClient> create(						// factory
		boost::asio::io_service&, scrolledLogWindow&);

	void connect(boost::asio::ip::tcp::endpoint&);

	void deliver(const message&	);									// the deliver methods
	//void deliver(const sqlLogin&);

private:

	void threadAction() {
	    m_ios.run();
	}

	// callbacks
	void handle_connect			(const boost::system::error_code& error);
	void handle_read_message	(const boost::system::error_code& error);
	void handle_write_message	(const boost::system::error_code& error);
	//void handle_write_sql_login	(const boost::system::error_code& error);

	void read_message();

	bool	m_closing	;											// is closing ?
	bool	m_connected	;											// is connected ?

	boost::asio::io_service&			m_ios		;				// asio components
	boost::asio::deadline_timer 		m_timer		;

	boost::shared_ptr<tcpConnection> 	m_connection;				// shared objects
	boost::shared_ptr<boost::thread>	m_thread	;

	scrolledLogWindow& m_scroll;

	message								m_message	;				// message i/o
	//sqlLogin							m_sqlLogin	;

	tcpClient(boost::asio::io_service&, scrolledLogWindow&);

};
#endif /* TCPCLIENT_HPP_ */
