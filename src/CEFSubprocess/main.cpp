#pragma warning(disable : 4100)

#include <include/cef_app.h>
#include <include/cef_browser.h>
#include <include/cef_client.h>
#include <include/cef_version.h>

#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>
#include <sstream>
#include <iomanip>
#include <functional>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

//
// helper function to convert a
// CefDictionaryValue to a CefV8Object
//
CefRefPtr<CefV8Value> to_v8object(CefRefPtr<CefDictionaryValue> const& dictionary)
{
    auto const obj = CefV8Value::CreateObject(nullptr, nullptr);
    if (dictionary)
    {
        auto const attrib = V8_PROPERTY_ATTRIBUTE_READONLY;
        CefDictionaryValue::KeyList keys;
        dictionary->GetKeys(keys);
        for (auto const& k : keys)
        {
            auto const type = dictionary->GetType(k);
            switch (type)
            {
            case VTYPE_BOOL:
                obj->SetValue(k, CefV8Value::CreateBool(dictionary->GetBool(k)), attrib);
                break;
            case VTYPE_INT:
                obj->SetValue(k, CefV8Value::CreateInt(dictionary->GetInt(k)), attrib);
                break;
            case VTYPE_DOUBLE:
                obj->SetValue(k, CefV8Value::CreateDouble(dictionary->GetDouble(k)), attrib);
                break;
            case VTYPE_STRING:
                obj->SetValue(k, CefV8Value::CreateString(dictionary->GetString(k)), attrib);
                break;

            default:
                break;
            }
        }
    }
    return obj;
}

class NirnLabSubprocessCefApp final : public CefApp
{
  public:
    NirnLabSubprocessCefApp() = default;

  private:
    IMPLEMENT_REFCOUNTING(NirnLabSubprocessCefApp);
};

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
    void* sandbox_info = nullptr;
#if defined(CEF_USE_SANDBOX)
    // Manage the life span of the sandbox information object. This is necessary
    // for sandbox support on Windows. See cef_sandbox_win.h for complete details.
    CefScopedSandboxInfo scoped_sandbox;
    sandbox_info = scoped_sandbox.sandbox_info();
#endif

    CefMainArgs main_args(hInstance);
    CefRefPtr<NirnLabSubprocessCefApp> app(new NirnLabSubprocessCefApp());

    return CefExecuteProcess(main_args, app, sandbox_info);
}
