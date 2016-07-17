Use py2.7 for twisted
Use Qt4 for twisted qt4reactor

pip install twisted
pip install pyserial
pip install numpy
sudo aptitude install liblapack-dev
sudo aptitude install gfortran
pip install scipy
sudo apt-get install cmake qt4-qmake qt-sdk python-dev
pip install --no-install sip --allow-external sip --allow-unverified sip
cd <>/build/sip
python configure.py
make
sudo make install
cd <>
wget ???
mv ~/Downloads/PyQt-x11-gpl-4.11.3.tar.gz .
tar xvzf PyQt-x11-gpl-4.11.3.tar.gz
cd PyQt-x11-gpl-4.11.3/
vim configure.py
  <change qmake to qmake-qt4>
python configure.py --verbose
make
make install
rm <install files>

##################################
#Guidata (not needed)

pip install guidata --allow-external guidata --allow-unverified guidata
pip install cython
pip install guiqwt --allow-external guiqwt --allow-unverified guiqwt
pip install spyder #for the guiqwt test launcher
#get and install qwt5.x
mv ~/Downloads/qwt-5.2.3.tar.bz2 .
qmake-qt4 qwt.pro
make
sudo make install
#get and install pyqwt5.x
mv ~/Downloads/PyQwt-5.2.0.tar.gz .
tar xvzf PyQwt-5.2.0.tar.gz
cd PyQwt-5.2.0/
cd configure/
vim configure.py
  <change qmake to qmake-qt4>
python configure.py -I/usr/local/qwt-5.2.3/include -L/usr/local/qwt-5.2.3/lib -lqwt
Problems:
  'excluded_features': ['-x HAS_PYQT_031105',
                       '-x HAS_NUMARRAY',
                       '-x HAS_NUMERIC',
                       '-x HAS_QWT4',
                       '-x HAS_QWT_SVG'],
make
make install
sudo aptitude install libhdf5-dev
pip install hpy5 #for the guiqwt test launcher
#######################################

pip install PIL --allow-external PIL --allow-unverified PIL
pip install qt4reactor
pip install pyqtgraph