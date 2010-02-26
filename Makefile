#
# Copyright (C) Velneo S.A. 2010 <velneo@velneo.com>
# 
# This file is part of libvrest
# vCurlDll is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# vCurlDll is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along
# with this program.  If not, see <http://www.gnu.org/licenses/>.
#

SRCPATH=.
LIBS=vCurlMain.c
SRCLIBS=$(SRCPATH)vCurlMain.c
#SRCTEST=$(SRCPATH)test.c



all: libs link

libs:  vCurlMain.c
	gcc -Wall -fPIC -c vCurlMain.c        
link:  vCurlMain.o
	gcc -shared -Wl,-soname,vlibCurl.so -o vlibCurl.so vCurlMain.o -lcurl
clean:
	rm *.o *.so *~




