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
# DZgameEngine/src makefile
#
#########################################################################
# Change Log
#------------------------------------------------------------------------
# 03-13-2015	added new object files to the list
# 03-01-2015	file created
#########################################################################


INC_DIR = $(PWD)/../include
INC_MOD_DIR = $(PWD)/../src_mod_xml
SDL_INC = /usr/include/SDL2
OBJ_DIR = $(PWD)/../obj

INCLUDE = $(INC_DIR)/*.h

CC = g++
CFLAGS = -Wall -ggdb -Og -I$(INC_DIR) -I$(SDL_INC) -I$(INC_MOD_DIR)
#CFLAGS = -Wall -O1 -s -I$(INC_DIR) -I$(INC_MOD_DIR)

LIBS =

APP_NAME = DZgameEngine

################################################
# list here all the object files
################################################
OBJ = \
$(OBJ_DIR)/DZlogger.o \
$(OBJ_DIR)/DZengine.o \
$(OBJ_DIR)/DZinputHandler.o \
$(OBJ_DIR)/DZkeyboard.o \
$(OBJ_DIR)/DZmouse.o \
$(OBJ_DIR)/DZjoystick.o \
$(OBJ_DIR)/DZtextureManager.o \
$(OBJ_DIR)/DZlayer.o \
$(OBJ_DIR)/DZlevel.o \
$(OBJ_DIR)/DZxmlParser.o \
$(OBJ_DIR)/DZstate.o \
$(OBJ_DIR)/DZstateMachine.o \
$(OBJ_DIR)/DZinitState.o \
$(OBJ_DIR)/DZcreateObject.o \
$(OBJ_DIR)/DZgraph.o \
$(OBJ_DIR)/DZsdlObject.o \
$(OBJ_DIR)/DZobject.o \
$(OBJ_DIR)/DZttf.o \
$(OBJ_DIR)/DZtimer.o \
$(OBJ_DIR)/DZsoundSystem.o \
$(END)

################################################
# Targets
################################################

$(APP_NAME): $(OBJ)
	-@echo "src make completed"

$(OBJ_DIR)/%.o: %.cpp $(INCLUDE)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	-@rm -f $(OBJ_DIR)/*.o *~ core $(INC_DIR)/*~

