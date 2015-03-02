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
# DZgameEngine/src_mod_xml makefile
#
# This makefile is used in place of the one provided with the tinyxml
# package. It compiles only the modules used by the game engine and
# puts the object files in the appropriate directory for linking with
# the rest of the application.
#
#########################################################################
# Change Log
#------------------------------------------------------------------------
# 03-01-2015	file created
#########################################################################

INC_DIR = .
OBJ_DIR = $(PWD)/../obj

INCLUDE = $(INC_DIR)/*.h

CC = g++
CFLAGS = -Wall -ggdb -Og -I$(INC_DIR)
#CFLAGS = -Wall -O1 -s -I$(INC_DIR)

LIBS =

APP_NAME = DZgameEngine

################################################
# list here all the object files
################################################
OBJ = \
$(OBJ_DIR)/tinyxml2.o \
$(END)

################################################
# Targets
################################################

$(APP_NAME): $(OBJ)
	-@echo " src_mod_xml make completed"

$(OBJ_DIR)/%.o: %.cpp $(INCLUDE)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	-@rm -f $(OBJ_DIR)/*.o *~ core $(INC_DIR)/*~

