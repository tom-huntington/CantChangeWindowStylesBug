#pragma once

#include "MainWindow.g.h"

namespace winrt::CantChangeWindowStyles::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        void myButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void myButton2_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    private:
        winrt::Microsoft::UI::Windowing::AppWindow GetAppWindowForCurrentWindow();

    };
}

namespace winrt::CantChangeWindowStyles::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
