#pragma once

#include "PCH.h"
#include "CEFService.h"
#include "Render/IRenderLayer.h"
#include "CEF/NirnLabCefApp.h"
#include "CEF/IBrowser.h"
#include "CEF/CEFBrowser.h"
#include "Menus/MultiLayerMenu.h"

namespace NL::Services
{
    class UIPlatformService
    {
      protected:
        std::shared_ptr<spdlog::logger> m_logger = nullptr;
        std::shared_ptr<CEFService> m_cefService = nullptr;
        std::shared_ptr<NL::CEF::CEFBrowser> m_defaultCefBrowser = nullptr;

      public:
        UIPlatformService(
            std::shared_ptr<spdlog::logger> a_logger,
            std::shared_ptr<CEFService> a_cefService);
        virtual ~UIPlatformService();

        /// <summary>
        /// Init ui service and it's dependencies
        /// </summary>
        /// <returns></returns>
        bool Init();

        /// <summary>
        /// Close ui service and it's dependencies
        /// </summary>
        void Shutdown();

        /// <summary>
        /// Get default browser impl
        /// </summary>
        /// <returns></returns>
        std::shared_ptr<NL::CEF::CEFBrowser> GetBrowser();

        /// <summary>
        /// Get default browser interface
        /// </summary>
        /// <returns></returns>
        std::shared_ptr<NL::CEF::IBrowser> GetBrowserInterface();
    };

    inline std::shared_ptr<NL::Services::UIPlatformService> g_uiPlatfromService = nullptr;
}
