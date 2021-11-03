# tree-inference-benchmark

Directions:

Please make sure on your system you have g++ installed.

Python LightGBM benchmark:
python3 bench-lightgbm.py. Please make sure you have the LightGBM package installed.

Treelite benchmark:
I have included the Treelite shared object in the repo, so you don't need to do the Treelite conversion yourself. As a result we don't depend on the treelite library at all. Simply compile predict.cpp against mymodel.so: g++ -O3 -L . treelitebench.cpp mymodel.so -o test. Run the executable: LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. ./test

172Tree benchmark:
172Tree depend on the cnpy library to read the custom data format (which is just a compressed set of numpy arrays). Please make sure you have the cnpy library installed following the directions here: https://github.com/rogersce/cnpy. You might need to install libz-dev for cnpy. Once you have cnpy installed, go ahead and compile the 172Tree benchmark: g++ -O3 -fopenmp 172bench.cc 172.so -lcnpy -o test. Run the executable: LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/ubuntu/cnpy/build/:. ./test. Please replace the path /home/ubuntu/cnpy/build with your own path to where libcnpy.so can be found in the cnpy/build directory.  
