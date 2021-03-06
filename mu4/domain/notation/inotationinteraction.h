//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2020 MuseScore BVBA and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//=============================================================================
#ifndef MU_DOMAIN_INOTATIONINTERACTION_H
#define MU_DOMAIN_INOTATIONINTERACTION_H

#include <QPointF>
#include <functional>

#include "async/notification.h"

#include "notationtypes.h"
#include "inotationinputstate.h"
#include "inotationselection.h"

namespace mu {
namespace domain {
namespace notation {
class INotationInteraction
{
public:
    virtual ~INotationInteraction() = default;

    // Put notes
    virtual void startNoteEntry() = 0;
    virtual void endNoteEntry() = 0;
    virtual void padNote(const Pad& pad) = 0;
    virtual void putNote(const QPointF& pos, bool replace, bool insert) = 0;
    virtual async::Notification noteAdded() const = 0;
    virtual INotationInputState* inputState() const = 0;
    virtual async::Notification inputStateChanged() const = 0;

    // Shadow note
    virtual void showShadowNote(const QPointF& p) = 0;
    virtual void hideShadowNote() = 0;
    virtual void paintShadowNote(QPainter* p) = 0;

    // Select
    virtual Element* hitElement(const QPointF& pos, float width) const = 0;
    virtual void select(Element* e, SelectType type, int staffIdx = 0) = 0;
    virtual INotationSelection* selection() const = 0;
    virtual async::Notification selectionChanged() const = 0;

    // Drag
    using IsDraggable = std::function<bool (const Element*)>;
    virtual bool isDragStarted() const = 0;
    virtual void startDrag(const std::vector<Element*>& elems, const QPointF& eoffset, const IsDraggable& isDrag) = 0;
    virtual void drag(const QPointF& fromPos, const QPointF& toPos, DragMode mode) = 0;
    virtual void endDrag() = 0;
    virtual async::Notification dragChanged() const = 0;

    // Move
    //! NOTE Perform operations on selected elements
    virtual void moveSelection(MoveDirection d, MoveSelectionType type) = 0;
    virtual void movePitch(MoveDirection d, PitchMode mode) = 0;  //! NOTE Requires a note to be selected
    virtual void moveText(MoveDirection d, bool quickly) = 0;     //! NOTE Requires a text element to be selected
};
}
}
}

#endif // MU_DOMAIN_INOTATIONINTERACTION_H
