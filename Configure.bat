@echo off
if not exist Dependencies (
	mkdir Dependencies
)
cd Dependencies
if exist RobotecGPULidar (
	git -C RobotecGPULidar pull origin
) else (
	git clone -b develop --single-branch --depth 1 https://github.com/carla-simulator/RobotecGPULidar.git RobotecGPULidar
)
if exist flat_hash_map (
	git -C flat_hash_map pull origin
) else (
	git clone --single-branch --depth 1 https://github.com/skarupke/flat_hash_map.git flat_hash_map
)
cd RobotecGPULidar
python setup.py --install-deps
cmake -B Build -G Ninja -S . -DCMAKE_INSTALL_PREFIX=%cd%/Install -DCMAKE_BUILD_TYPE=Release -DRGL_BUILD_TESTS=OFF -DRGL_BUILD_TAPED_TESTS=OFF -DRGL_BUILD_TOOLS=OFF -DRGL_BUILD_STATIC=ON
cmake --build Build
cd ..
cd ..