using System.Runtime.InteropServices;
internal class MarchHare
{
    [STAThread] static void Main()
    {
        ApplicationConfiguration.Initialize();
        #if DEBUG
        Debug();
        #endif 
        Application.Run(new App.UI());
    }

    [DllImport("kernel32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    private static extern bool AllocConsole();
    static void Debug()
    {
        AllocConsole();

    }
}