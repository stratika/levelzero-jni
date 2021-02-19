package uk.ac.manchester.tornado.drivers.spirv.levelzero;

import java.util.Arrays;

public class ZeComputeProperties {

    private int type;
    private long pNext;
    private int maxTotalGroupSize;

    private int maxGroupSizeX;
    private int maxGroupSizeY;
    private int maxGroupSizeZ;
    private int maxGroupCountX;
    private int maxGroupCountY;
    private int maxGroupCountZ;
    private int maxSharedLocalMemory;
    private int numSubGroupSizes;

    private int[] subGroupSizes;

    public ZeComputeProperties() {
        type = Ze_Structure_Type.ZE_STRUCTURE_TYPE_DEVICE_COMPUTE_PROPERTIES;
    }

    public String toString() {
        StringBuffer buffer = new StringBuffer();
        buffer.append("=========================\n");
        buffer.append("Device Compute Properties\n");
        buffer.append("=========================\n");
        buffer.append("Type                : " + ZeUtils.zeTypeToString(type) + "\n");
        buffer.append("pNext               : " + pNext + "\n");
        buffer.append("maxTotalGroupSize   : " + maxTotalGroupSize + "\n");
        buffer.append("maxGroupSizeX       : " + maxGroupSizeX + "\n");
        buffer.append("maxGroupSizeY       : " + maxGroupSizeY + "\n");
        buffer.append("maxGroupSizeZ       : " + maxGroupSizeZ + "\n");
        buffer.append("maxGroupCountX      : " + maxGroupCountX + "\n");
        buffer.append("maxGroupCountY      : " + maxGroupCountY + "\n");
        buffer.append("maxGroupCountZ      : " + maxGroupCountZ + "\n");
        buffer.append("maxSharedLocalMemory: " + maxSharedLocalMemory + "\n");
        buffer.append("numSubGroupSizes    : " + numSubGroupSizes + "\n");
        buffer.append("subGroupSizes       : " + Arrays.toString(subGroupSizes) + "\n");
        return buffer.toString();
    }

    public int getType() {
        return type;
    }

    public long getpNext() {
        return pNext;
    }

    public int getMaxTotalGroupSize() {
        return maxTotalGroupSize;
    }

    public int getMaxGroupSizeX() {
        return maxGroupSizeX;
    }

    public int getMaxGroupSizeY() {
        return maxGroupSizeY;
    }

    public int getMaxGroupSizeZ() {
        return maxGroupSizeZ;
    }

    public int getMaxGroupCountX() {
        return maxGroupCountX;
    }

    public int getMaxGroupCountY() {
        return maxGroupCountY;
    }

    public int getMaxGroupCountZ() {
        return maxGroupCountZ;
    }

    public int getMaxSharedLocalMemory() {
        return maxSharedLocalMemory;
    }

    public int getNumSubGroupSizes() {
        return numSubGroupSizes;
    }

    public int[] getSubGroupSizes() {
        return subGroupSizes;
    }

}
