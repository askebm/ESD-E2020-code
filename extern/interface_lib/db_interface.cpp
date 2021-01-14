/*
 * database_interface.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: Catalin I. Ntemkas
 */
#include "db_interface.hpp"

void my_free (void *data, void *hint)
{
 free (data);
}
DatabaseInterface::DatabaseInterface() {
	// TODO Auto-generated constructor stub
	context = NULL;
	responder = NULL;
}

DatabaseInterface::~DatabaseInterface() {
	// TODO Auto-generated destructor stub
	zmq_close(responder);
	zmq_ctx_destroy(context);
}

DatabaseInterface::DatabaseInterface(ServerAddress ip, ServerPort port) {
	context = zmq_ctx_new();

	responder = zmq_socket(context, ZMQ_REQ);
	std::string tcp_address = "tcp://" + ip + ":" + port;
	zmq_connect(responder, tcp_address.c_str());

}

std::string DatabaseInterface::sendRequest(std::string request) {
	//================================================= Send request message
	//======================================= Send request msg size
	std::string request_size_msg = //To be filled in. This contains the size of the message 	
		// (actual request) that will be sent to the server later on.
		
	zmq_send(responder, request_size_msg.c_str(), request_size_msg.length(), 0);
	std::cout << "Sending: " << request_size_msg << std::endl;

	//======================================= Await for ack from server
	char ack_buffer[ACK_MSG.length()+1] = "";
	zmq_recv(responder, ack_buffer, ACK_MSG.length(), 0);
	ack_buffer[ACK_MSG.length()] = '\0';

	//======================================= Send request message
	zmq_send(responder, request.c_str(), request.length(), 0);
	std::cout << "Requesting: " << request << std::endl;

	//======================================= Get reply msg size
	char msg_size_buffer[MSG_SIZE_BUFFER_SIZE] = "";
	zmq_recv(responder, msg_size_buffer, MSG_SIZE_BUFFER_SIZE, 0);

	//======================================= Allocate buffer
	int msg_size = 	//To be filled in. We need to assign a size for the buffer that will receive
	   				//the reply message.	
	char reply_msg_buffer[msg_size] = "";

	//======================================= Send ack to server
	zmq_send(responder, ACK_MSG.c_str(), ACK_MSG.length(), 0);
	std::cout << "Acknowledging server msg: " << ACK_MSG << std::endl; 
	//======================================= Get reply message
	zmq_recv(responder, reply_msg_buffer, msg_size, 0);
	reply_msg_buffer[msg_size] = '\0';

	std::cout << std::endl;
	return (std::string)reply_msg_buffer;
}

SimpleItem DatabaseInterface::getSimpleItemById(ItemId id) {
	return SimpleItem(getItemById(id));
}

SimpleItem DatabaseInterface::getSimpleItemByName(Name name) {
	return SimpleItem(getItemByName(name));
}

SimpleItem DatabaseInterface::getSimpleItemByBarcode(Barcode barcode) {
	return SimpleItem(getItemByBarcode(barcode));
}

Receipt DatabaseInterface::getReceiptByNumber(ReceiptNumber number){
	//To be filled in
}

Item DatabaseInterface::getItemById(ItemId id) {
	//To be filled in
}

Item DatabaseInterface::getItemByName(Name name) {
	//To be filled in
}

Item DatabaseInterface::getItemByBarcode(Barcode barcode) {
	//To be filled in
}

Receipt DatabaseInterface::createNewReceipt() {
	//To be filled in
}

void DatabaseInterface::completeTransaction(Receipt receipt) {
	//To be filled in

}
PaymentStatus DatabaseInterface::getPaymentStatusPayed() {
	return DB_RECEIPT_PAYED;
}

PaymentStatus DatabaseInterface::getPaymentStatusCancelled() {
	return DB_RECEIPT_CANCELLED;
}

