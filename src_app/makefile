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
# 03-01-2015	file created
#########################################################################


INC_DIR = $(PWD)/../include
SDL_INC = /usr/include/SDL2
OBJ_DIR = $(PWD)/../obj

INCLUDE = $(INC_DIR)/*.h

CC = g++
CFLAGS = -Wall -ggdb -Og -I$(INC_DIR) -I$(SDL_INC)
#CFLAGS = -Wall -O1 -s -I$(INC_DIR) -I$(SDL_INC)

LIBS =

APP_NAME = DZgameEngine

################################################
# list here all the object files
################################################
OBJ = \
$(OBJ_DIR)/main.o \
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

