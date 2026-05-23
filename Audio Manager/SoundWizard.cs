using System.Runtime.InteropServices;

namespace Sonora;
public static class SoundWizard
{
    public static int deviceIndex;

    [DllImport("nd_audio.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
    public static extern int getAudioDeviceNames([In, Out] IntPtr[]? arr);
    public static string[] GetDevices() 
    {
        try {
            int nDevices = getAudioDeviceNames(null);
            if (nDevices <= 0) return [];

            IntPtr[] ptrArr = new IntPtr[nDevices];

            getAudioDeviceNames(ptrArr);

            string[] devices = new string[nDevices];
            for (int i = 0; i < nDevices; ++i)
            {
                devices[i] = Marshal.PtrToStringUni(ptrArr[i]) ?? string.Empty;
            }
            return devices;
            
        }
        catch (DllNotFoundException) {
            Console.WriteLine("ERROR: 'nd_audio.dll' not found."); }
        catch (System.EntryPointNotFoundException) {
            Console.WriteLine("ERR: Entry not found for getting device names"); }
        catch (Exception) {
            Console.WriteLine("ERR: Unexpected error ocurred.");
        }
        return [];
    }
}
