.pragma library
/* This file */

function _newItem(_data, _align, _url) {
    var _item = {};
    _item.data = _data;
    _item.align = function( _row, _rowspan, _col, _colspan) {

        this.row = _row;
        this.rowspan = _rowspan;
        this.column = _col;
        this.columnspan = _colspan;
        this.checkable = true;
    }
    _item.align.apply(_item, _align);
    _item.source = _url === undefined ?
          Qt.resolvedUrl("../AutopilotItems/BaseButton.qml"):
          Qt.resolvedUrl(_url);

    return _item;
}

function createItems() {

    var _items = [];
    _items.push(_newItem("AP", [2, 1, 0, 1] ));
    _items.push(_newItem("HDG", [2, 1, 2, 1] ));
    _items.push(_newItem("NAV", [2, 1, 3, 1] ));
    _items.push(_newItem("APR", [2, 1, 4, 1] ));
    _items.push(_newItem("REV", [2, 1, 5, 1] ));
    _items.push(_newItem("ALT", [2, 1, 6, 1] ));
    _items.push(_newItem("UP", [1, 1, 7, 1] ));
    _items.push(_newItem("DN", [2, 1, 7, 1] ));
    _items.push(_newItem("ARM", [0, 1, 8, 1] ));
    _items.push(_newItem("BAR0", [0, 1, 9, 1] ));
    _items.push(_newItem("display", [0, 2, 1, 6], "../AutopilotItems/Display.qml"));
    _items.push(_newItem("dial", [1, 2, 8, 2], "../AutopilotItems/Dial.qml"));

    return _items;
}

function newAutopilot() {
  var autopilot = {};
  autopilot.activated = false;
  autopilot.items = createItems();
  return autopilot;
}
