/***************************************************************************
                          soundsourcemp3.h  -  description
                             -------------------
    begin                : Wed Feb 20 2002
    copyright            : (C) 2002 by Tue and Ken Haste Andersen
    email                : 
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef SOUNDSOURCEMP3_H
#define SOUNDSOURCEMP3_H

#include <qobject.h>
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include "mad.h"
#include "errno.h"
#include "soundsource.h"
#include <sys/types.h>
#include <qfile.h>
//#include <sys/stat.h>
//#include <unistd.h>
#include <id3tag.h>

/**
  *@author Tue and Ken Haste Andersen
  */
class TrackInfoObject;
  
class SoundSourceMp3 : public SoundSource {
public:
    SoundSourceMp3( QString );
    ~SoundSourceMp3();
    long seek(long);
    unsigned read(unsigned long size, const SAMPLE*);
    inline long unsigned length();
    static int ParseHeader( TrackInfoObject * );
    
private:
    /** Fills the string str with the content of the id3tag frame of frameid.
      * If the frame does not exist or is empty the string is left untouched. */
    static void getField(id3_tag *tag, const char *frameid, QString str);

    FILE *file;
    int bitrate;
    int framecount;
    int currentframe;
    mad_timer_t pos;              /* current play position. */
    mad_timer_t filelength;
    mad_stream Stream;
    mad_frame Frame;
    mad_synth Synth;
    unsigned inputbuf_len;
    char *inputbuf;
    /** Start index in Synth buffer of samples left over from previous call to read */
    int rest;
};


#endif
