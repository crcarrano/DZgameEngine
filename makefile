# #######################################################################
# Copyright (C) 2015 Carlo Carrano 
# crc@dazzlingsolutions.com
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; version 2 of the License.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
# USA
# #######################################################################
#
# DZgameEngine master makefile

SRC_DIR = $(PWD)/src
SRC_MOD_DIR = $(PWD)/src_mod
SRC_APP_DIR = $(PWD)/src_app

APP_NAME = DZgameEngine

OBJ_DIR = $(PWD)/obj
OBJ = $(OBJ_DIR)/*.o

BIN_DIR = $(PWD)/bin

CC = g++
CFLAGS = -Wall -ggdb -Og 

LIBS = `sdl2-config --cflags --libs`

# Targets
.PHONY: clean $(APP_NAME)

$(APP_NAME):
	-@(cd $(SRC_DIR) ; make)
#	-@(cd $(SRC_MOD_DIR) ; make)
#	-@(cd $(SRC_APP_DIR) ; make);
	$(CC) -o $(BIN_DIR)/$(APP_NAME) $(OBJ) $(CFLAGS) $(LIBS)

clean:
	-@(cd $(SRC_DIR) ; make clean)
#	-@(cd $(SRC_MOD_DIR) ; make clean)
#	-@(cd $(SRC_APP_DIR) ; make clean)
