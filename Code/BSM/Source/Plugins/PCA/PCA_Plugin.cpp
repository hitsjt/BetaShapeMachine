#include "PCA_Plugin.hpp"

namespace SNL {;
namespace PCA {;

static PCA_Plugin * plugin = NULL;

/** DLL start routine. Installs plugin. */
extern "C" SNL_PCA_API SNL::Plugin *
	dllStartPlugin()
{
	plugin = new PCA_Plugin();
	SNL::PluginManager::install(plugin);
	return plugin;
}

/** DLL stop routine. Uninstalls plugin. */
extern "C" SNL_PCA_API void
	dllStopPlugin()
{
	SNL::PluginManager::uninstall(plugin);
	delete plugin;
}

static std::string const PCA_PLUGIN_NAME   =  "PCA Network";
static std::string const PCA_NETWORK_NAME  =  "PCA";

PCA_Plugin::PCA_Plugin()
	: SNL::Plugin(PCA_PLUGIN_NAME), started(false)
{}

PCA_Plugin::~PCA_Plugin()
{
	uninstall();
}

bool
	PCA_Plugin::install()
{
	return true;
}

bool
	PCA_Plugin::startup()
{
  if (!started)
  {
    started = true;
  }
	return true;
}

bool
	PCA_Plugin::shutdown()
{
  if (started)
  {
    started = false;
  }

	return true;
}

bool
	PCA_Plugin::uninstall()
{
	if (shutdown())  // not currently dependent on presence of other plugins
		return true;
	else
		return false;
}

} // namespace PCA
} // namespace SNL
