mkdir -p Dependencies
cd Dependencies
if [ -d "RobotecGPULidar" ]; then
	git -C RobotecGPULidar pull origin
else
	git clone -b develop https://github.com/carla-simulator/RobotecGPULidar.git RobotecGPULidar
fi
cd RobotecGPULidar
python3 setup.py --install-deps
cmake -B Build -G Ninja -S . -DCMAKE_INSTALL_PREFIX=$PWD/Install -DCMAKE_BUILD_TYPE=Release -DRGL_BUILD_TESTS=OFF -DRGL_BUILD_TAPED_TESTS=OFF -DRGL_BUILD_TOOLS=OFF -DRGL_BUILD_STATIC=ON
cmake --build Build
cd ..
cd ..
