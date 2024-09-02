package uk.ac.manchester.tornado.drivers.spirv.levelzero.sysman;

/**
 * Abstraction of a LevelZero Driver. A LevelZero driver is composed of one or
 * more physical devices.
 */
public class PowerFunctions {

    static {
        // Use -Djava.library.path=./levelZeroLib/build/
        System.loadLibrary("tornado-levelzero");
    }

    public PowerFunctions() {

    }

    private native int zesDeviceEnumPowerDomains_native(long deviceHandler, int[] numPowerDomains, long[] hMemory);

    public int zesDeviceEnumPowerDomains(long deviceHandler, int[] numPowerDomains, long[] hMemory) {
        int result = zesDeviceEnumPowerDomains_native(deviceHandler, numPowerDomains, hMemory);
        return result;
    }
}
