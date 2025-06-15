echo "Post build script started"

BuildArtifactFileName="../build/rzg2l_cm33_rpmsg_demo.elf"

if [ -n "$BuildArtifactFileName" ]; then
	inputfilename=$BuildArtifactFileName
fi
if [ -n "$BUILDARTIFACTFILENAME" ]; then
	inputfilename=$BUILDARTIFACTFILENAME
fi

filebody=${inputfilename%.*}

arm-none-eabi-objcopy -O binary -j .secure_vector ${inputfilename} ${filebody}_secure_vector.bin
arm-none-eabi-objcopy -O binary -j .non_secure_vector ${inputfilename} ${filebody}_non_secure_vector.bin
arm-none-eabi-objcopy -O binary -j .secure_code ${inputfilename} ${filebody}_secure_code.bin
arm-none-eabi-objcopy -O binary -j .non_secure_code -j .data ${inputfilename} ${filebody}_non_secure_code.bin

echo "Post build script complete"
