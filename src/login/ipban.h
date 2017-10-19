/**
 * @file ipban.h
 * Module purpose is to read configuration for login-server and handle accounts,
 *  and also to synchronize all login interfaces: loginchrif, loginclif, logincnslif.
 * Licensed under GNU GPL.
 *  For more information, see LICENCE in the main folder.
 * @author Athena Dev Teams < r15k
 * @author rAthena Dev Team
 */

#pragma once
#ifndef __IPBAN_H_INCLUDED__
#define __IPBAN_H_INCLUDED__

#include <memory>
#include "../common_old/cbasetypes.h"

namespace ra {
namespace login {
class c_ModuleIpBan {
private:
	struct pImpl;
	std::unique_ptr<pImpl> aPimpl;

private:
	c_ModuleIpBan();
	static int ipban_cleanup(int tid, unsigned int tick, int id, intptr_t data);

public:
	static c_ModuleIpBan &smGetInstance();

	/**
	 * Check if ip is in the active bans list.
	 * @param ip: ipv4 ip to check if ban
	 * @return true if found or error, false if not in list
	 */
	bool ipban_check(uint32 ip);

	/**
	 * Log a failed attempt.
	 *  Also bans the user if too many failed attempts are made.
	 * @param ip: ipv4 ip to record the failure
	 */
	void ipban_log(uint32 ip);

	/**
	 * Read configuration options.
	 * @param key: config keyword
	 * @param value: config value for keyword
	 * @return true if successful, false if config not complete or server already running
	 */
	bool ipban_config_read(const char *key, const char *value);

	/**
	 * Initialize the module.
	 * Launched at login-serv start, create db or other long scope variable here.
	 */
	void ipban_init(void);

	/**
	 * Destroy the module.
	 * Launched at login-serv end, cleanup db connection or other thing here.
	 */
	void ipban_final(void);
};
}
}
#endif // __IPBAN_H_INCLUDED__
