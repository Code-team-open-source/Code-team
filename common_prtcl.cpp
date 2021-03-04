#include "tool.h"
enum tool_type {
	button,
	slider
};

void Tool::serialize(int stream) virtual const
{  	
	int size = tool_text.size();
	size = htons(size);
	send(stream, &size, sizeof(int));
	send(stream, tool_text.c_str(), size);
	int pos_l_c = htonl(position.left_upper_corner);
	int pos_r_c = htonl(position.right_lower_corner);
	send(stream, &pos_l_c, sizeof(int));
	send(stream, &pos_r_c, sizeof(int));
}

void Button::serialize() {
	int type = htonl(tool_type::button);
	send(stream, type, sizeof(int));
	Tool::serialize();
}

void Slider::serialize() {
	int type = htonl(tool_type::slider);
	send(stream, type, sizeof(int));
	Tool::serialize();
}


void Tool::deserialize (int stream) virtual
{	
	int size = 0;
	recv(stream, &size, sizeof(int));
  	size = ntohs(size);
  	std::vector<char> b();
  	b.resize(size+1);
  	recv(stream, &b[0], l);
  	tool_text = std::string(&b[0], l);
  	int pos_l_c = 0;
  	int pos_r_c = 0;
	recv(stream, &pos_l_c, sizeof(int));
	position.left_upper_corner = ntohs(pos_l_c);  
	recv(stream, &pos_r_c, sizeof(int));  
	position.right_lower_corner = ntohs( pos_r_c );  
}

// enum protocol_type{
// 	tools, message, change_tool
// };

socket get_socket() {
	return socket_
}

int send_tools(vector<Tool>& tools) {

	int size = htonl(tools.size());
	socket sock = get_socket();
	
	send(sock, &size, sizeof(int));
	for (auto i : tools)
	{
		i.serialize();
	}
}

int get_tools(vector<Tool> &tools) {
	tools.clear();
	int size = 0;
	recv(sock, &size, sizeof(int));
	size = ntohs(size);
	for (int i = 0; i < size; ++i)
	{
		tool_type tool_type_ = 0;
		recv(sock, &tool_type_, sizeof(tool_type));
		tool_type_ = ntohs(tool_type_);
		if (tool_type_ == button) {
			Button butt;
			butt.deserialize();
			tools.push_back(butt);
		}
	}
}



int send_message(string s) {
	socket sock = get_socket();
	size = htonl(s.size);
	send(sock, &size, sizeof(int));
	send(sock, c_str(s), size);
}

std::string get_message(string m) {
	int size = 0;
	recv(sock, &size, sizeof(int));
	size = ntohs(size);
	std::vector<char> b();
  	b.resize(size+1);
  	recv(stream, &b[0], l);
  	string s = std::string(&b[0], l);
}


// int send_change_tool() {

// }


// int send_change_tool() {

// }