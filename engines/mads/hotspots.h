/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef MADS_HOTSPOTS_H
#define MADS_HOTSPOTS_H

#include "common/scummsys.h"
#include "mads/events.h"
#include "mads/player.h"

namespace MADS {

class MADSEngine;

class DynamicHotspot {
public:
	bool _active;
	int _seqIndex;
	Common::Rect _bounds;
	Common::Point _feetPos;
	Facing _facing;
	int _descId;
	int _verbId;
	int _articleNumber;
	CursorType _cursor;

	/**
	 * Constructor
	 */
	DynamicHotspot();

	/**
	 * Synchronize the data
	 */
	void synchronize(Common::Serializer &s);
};

#define DYNAMIC_HOTSPOTS_SIZE 8

class DynamicHotspots {
private:
	MADSEngine *_vm;
	Common::Array<DynamicHotspot> _entries;
	int _count;
public:
	bool _changed;
public:
	DynamicHotspots(MADSEngine *vm);

	Common::Array<MADS::DynamicHotspot>::size_type size() const { return _entries.size(); }
	DynamicHotspot &operator[](uint idx) { return _entries[idx]; }
	int add(int descId, int verbId, int seqIndex, const Common::Rect &bounds);
	int setPosition(int index, const Common::Point &pos, Facing facing);
	int setCursor(int index, CursorType cursor);
	void remove(int index);
	void clear();
	void reset();
	void refresh();

	/**
	* Synchronize the data
	*/
	void synchronize(Common::Serializer &s);
};

class Hotspot {
public:
	Common::Rect _bounds;
	Common::Point _feetPos;
	Facing _facing;
	int _articleNumber;
	bool _active;
	CursorType _cursor;
	int _vocabId;
	int _verbId;

	Hotspot();
	Hotspot(Common::SeekableReadStream &f, bool isV2);
};

class Hotspots : public Common::Array<Hotspot> {
private:
	MADSEngine *_vm;
public:
	Hotspots(MADSEngine *vm) : _vm(vm) {}

	/**
	 * Sets the active state of a given hotspot
	 */
	void activate(int vocabId, bool active);
};

} // End of namespace MADS

#endif	/* MADS_HOTSPOTS_H */