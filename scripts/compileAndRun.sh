mvn clean package
clang -cc1 -triple spir copy_data.cl -O0 -finclude-default-header -emit-llvm-bc -o opencl-copy.bc
llvm-spirv opencl-copy.bc -o opencl-copy.spv
cp opencl-copy.spv /tmp/opencl-copy.spv

java -Djava.library.path=./levelZeroLib/build -cp target/levelzero-0.1.0.jar uk.ac.manchester.tornado.drivers.spirv.levelzero.samples.TestLevelZero

