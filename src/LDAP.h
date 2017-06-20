// Generated by binpac_quickstart

#ifndef ANALYZER_PROTOCOL_LDAP_LDAP_H
#define ANALYZER_PROTOCOL_LDAP_LDAP_H

#include "analyzer/protocol/tcp/TCP.h"
#include "events.bif.h"
#include "ldap_pac.h"

namespace analyzer { namespace LDAP {

class LDAP_Analyzer

: public tcp::TCP_ApplicationAnalyzer {

typedef struct {
    unsigned char *ldap_buf;
	int64 ldap_buf_len;
	int64 processed_len;
	bool building_packet;
} Endpoint;

public:
	LDAP_Analyzer(Connection* conn);
	virtual ~LDAP_Analyzer();

	// Overriden from Analyzer.
	virtual void Done();
	
	virtual void DeliverStream(int len, const u_char* data, bool orig);
	virtual void Undelivered(uint64 seq, int len, bool orig);

	// Overriden from tcp::TCP_ApplicationAnalyzer.
	virtual void EndpointEOF(bool is_orig);

	static analyzer::Analyzer* InstantiateAnalyzer(Connection* conn)
		{ return new LDAP_Analyzer(conn); }

protected:
	binpac::LDAP::LDAP_Conn* interp;
	bool had_gap;
	int packet_counter;
	
	Endpoint endp_orig;
	Endpoint endp_resp;
};

} } // namespace analyzer::* 

#endif