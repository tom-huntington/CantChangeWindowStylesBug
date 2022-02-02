#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::CantChangeWindowStyles::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
    }

    void MainWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
        HWND hwnd;
        this->try_as<IWindowNative>()->get_WindowHandle(&hwnd);

        auto print_styles = [=]()
        {
            auto styles = GetWindowLongPtrA(hwnd, GWL_STYLE);

            std::stringstream ss{};
            ss << styles << std::endl;
            for (unsigned i = 63; i < 64; i--)
                ss << (((1ull << i) & styles) != 0);
            ss << std::endl;
            OutputDebugStringA(ss.str().c_str());
        };
        print_styles();
        SetWindowLongPtrA(hwnd, GWL_STYLE, 0);
        print_styles();
    }
}


void winrt::CantChangeWindowStyles::implementation::MainWindow::myButton2_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    GetAppWindowForCurrentWindow();
}

winrt::Microsoft::UI::Windowing::AppWindow winrt::CantChangeWindowStyles::implementation::MainWindow::GetAppWindowForCurrentWindow()
{
    // Get access to IWindowNative
    winrt::CantChangeWindowStyles::MainWindow thisWindow = *this;
    winrt::com_ptr<IWindowNative> windowNative = thisWindow.as<IWindowNative>();

    //Get the HWND for the XAML Window
    HWND hWnd;
    windowNative->get_WindowHandle(&hWnd);

    // Get the WindowId for our window
    winrt::Microsoft::UI::WindowId windowId;
    windowId = winrt::Microsoft::UI::GetWindowIdFromWindow(hWnd);

    // Get the AppWindow for the WindowId
    Microsoft::UI::Windowing::AppWindow appWindow = Microsoft::UI::Windowing::AppWindow::GetFromWindowId(windowId);

    return appWindow;
}
