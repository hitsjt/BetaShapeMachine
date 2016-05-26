#include "DL13_Plugin.hpp"
#include "DL13_NetworkFactory.hpp"

namespace SNL {;
namespace DL13 {;

static DL13_Plugin * plugin = NULL;

/** DLL start routine. Installs plugin. */
extern "C" SNL_DL13_API SNL::Plugin *
	dllStartPlugin()
{
	plugin = new DL13_Plugin();
	SNL::PluginManager::install(plugin);
	return plugin;
}

/** DLL stop routine. Uninstalls plugin. */
extern "C" SNL_DL13_API void
	dllStopPlugin()
{
	SNL::PluginManager::uninstall(plugin);
	delete plugin;
}

static std::string const DL13_PLUGIN_NAME   =  "DL13 Network";
static std::string const DL13_NETWORK_NAME  =  "DL13";

DL13_Plugin::DL13_Plugin()
	: SNL::Plugin(DL13_PLUGIN_NAME), factory(NULL), started(false)
{}

DL13_Plugin::~DL13_Plugin()
{
	uninstall();
}

bool
	DL13_Plugin::install()
{
	return true;
}

bool
	DL13_Plugin::startup()
{
	if (!started)
	{
		if (!factory)
			factory = new DL13_NetworkFactory;

		SNL::NetworkManager::installFactory(DL13_NETWORK_NAME, factory);
		started = true;
	}

	return true;
}

bool
	DL13_Plugin::shutdown()
{
	if (started)
	{
		factory->destroyAllNetworks();
		SNL::NetworkManager::uninstallFactory(DL13_NETWORK_NAME);
		started = false;
	}

	return true;
}

bool
	DL13_Plugin::uninstall()
{
	if (shutdown())  // not currently dependent on presence of other plugins
	{
		delete factory;
		factory = NULL;

		return true;
	}
	else
		return false;
}

} // namespace DL13
} // namespace SNL
