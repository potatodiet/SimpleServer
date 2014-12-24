#include "Request.hh"

#include <sstream>
#include <vector>

ss::http::Request::Request(const std::string& headers_string)
{
	parse_headers(headers_string);
}

void ss::http::Request::parse_headers(const std::string& headers_string)
{
	std::istringstream headers_stream(headers_string);

	std::string method;
	std::getline(headers_stream, method, ' ');
	this->headers["method"] = method;

	std::string location;
	std::getline(headers_stream, location, ' ');
	this->headers["location"] = location;

	std::string protocol;
	std::getline(headers_stream, protocol);
	// Quick fix to get rid of trailing cariage return
	this->headers["protocol"] = protocol.substr(0, protocol.size() - 1);

	std::vector<std::string> tokens;
	for (std::string each; std::getline(headers_stream, each); tokens.push_back(each));

	for (const auto& header : tokens)
	{
		const auto& split_pos = header.find(':');
		if (split_pos != std::string::npos)
		{
			const auto& key = header.substr(0, split_pos);
			const auto& value = header.substr(split_pos);
			// Cutoff leading splitting key and space
			headers[key] = value.substr(2);
		}
	}
}