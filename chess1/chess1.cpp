
#include "chess1.h"
#include <QMouseEvent>
#define GetRowCol(__row, __col, __id) \
int __row = _s[__id]._row;\
int __col = _s[__id]._col

chess1::chess1(QWidget* parent) :
	QFrame(parent)
{
	this->_r = 20;
	setMinimumSize(_r * 18 + 1, _r * 20 + 1);
	init(true);


}


chess1::~chess1()
{

}

void chess1::init(bool bRedSide)
{
	for (int i = 0; i < 32; ++i)
	{
		_s[i].init(i);
	}
	if (bRedSide)
	{
		for (int i = 0; i < 32; ++i)
		{
			_s[i].rotate();
		}
	}

	_selectid = -1;
	_bRedTurn = true;
	_bSide = bRedSide;
	update();
}

void chess1::paintEvent(QPaintEvent*)
{
	int r = height() / 20;
	_r = r;
	_off = QPoint(r + 1, r + 1);

	QPainter p(this);
	p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

	p.save();
	drawPlate(p);
	p.restore();

	p.save();
	drawPlace(p);
	p.restore();

	p.save();
	drawInitPosition(p);
	p.restore();

	p.save();
	drawStone(p);
	p.restore();
}

void chess1::drawStone(QPainter& p)
{
	for (int i = 0; i < 32; i++)
	{
		drawStone(p, i);
	}
}

bool chess1::isDead(int id)
{
	if (id == -1)return true;
	return _s[id]._dead;
}

void chess1::drawStone(QPainter& p, int id)
{
	if (isDead(id)) return;
	QColor color;
	if (red(id)) color = Qt::yellow;
	else color = Qt::black;

	p.setPen(QPen(QBrush(color), 2));

	if (id == _selectid) p.setBrush(Qt::gray);
	else p.setBrush(Qt::gray);

	p.drawEllipse(cell(id));

	p.setFont(QFont("system", _r * 1.2, 700));
	p.drawText(cell(id), name(id), QTextOption(Qt::AlignCenter));
}

QString chess1::name(int id)
{
	return _s[id].name();
}

bool chess1::red(int id)
{
	return _s[id]._red;
}

void chess1::drawInitPosition(QPainter& p, int row, int col)
{
	QPoint pt = center(row, col);
	QPoint off = QPoint(_r / 6, _r / 6);
	int len = _r / 3;

	QPoint ptStart;
	QPoint ptEnd;

	if (col != 0)
	{
		/* 左上角 */
		ptStart = QPoint(pt.x() - off.x(), pt.y() - off.y());
		ptEnd = ptStart + QPoint(-len, 0);
		p.drawLine(ptStart, ptEnd);
		ptEnd = ptStart + QPoint(0, -len);
		p.drawLine(ptStart, ptEnd);

		/* 左下角 */
		ptStart = QPoint(pt.x() - off.x(), pt.y() + off.y());
		ptEnd = ptStart + QPoint(-len, 0);
		p.drawLine(ptStart, ptEnd);
		ptEnd = ptStart + QPoint(0, +len);
		p.drawLine(ptStart, ptEnd);
	}

	if (col != 8)
	{
		/* 右下角 */
		ptStart = QPoint(pt.x() + off.x(), pt.y() + off.y());
		ptEnd = ptStart + QPoint(+len, 0);
		p.drawLine(ptStart, ptEnd);
		ptEnd = ptStart + QPoint(0, +len);
		p.drawLine(ptStart, ptEnd);

		/* 右上角 */
		ptStart = QPoint(pt.x() + off.x(), pt.y() - off.y());
		ptEnd = ptStart + QPoint(+len, 0);
		p.drawLine(ptStart, ptEnd);
		ptEnd = ptStart + QPoint(0, -len);
		p.drawLine(ptStart, ptEnd);
	}
}

void chess1::drawInitPosition(QPainter& p)
{
	drawInitPosition(p, 3, 0);
	drawInitPosition(p, 3, 2);
	drawInitPosition(p, 3, 4);
	drawInitPosition(p, 3, 6);
	drawInitPosition(p, 3, 8);

	drawInitPosition(p, 6, 0);
	drawInitPosition(p, 6, 2);
	drawInitPosition(p, 6, 4);
	drawInitPosition(p, 6, 6);
	drawInitPosition(p, 6, 8);

	drawInitPosition(p, 2, 1);
	drawInitPosition(p, 2, 7);

	drawInitPosition(p, 7, 1);
	drawInitPosition(p, 7, 7);
}

void chess1::drawPlace(QPainter& p)
{
	p.drawLine(center(0, 3), center(2, 5));
	p.drawLine(center(2, 3), center(0, 5));

	p.drawLine(center(9, 3), center(7, 5));
	p.drawLine(center(7, 3), center(9, 5));
}

void chess1::drawPlate(QPainter& p)
{
	for (int i = 0; i < 10; ++i)
	{
		if (i == 0 || i == 9)
		{
			p.setPen(QPen(Qt::black, 3, Qt::SolidLine));
		}
		else
		{
			p.setPen(QPen(Qt::black, 1, Qt::SolidLine));
		}
		p.drawLine(center(i, 0), center(i, 8));
	}

	for (int i = 0; i < 9; ++i)
	{
		if (i == 0 || i == 8)
		{
			p.setPen(QPen(Qt::black, 3, Qt::SolidLine));
			p.drawLine(center(0, i), center(9, i));
		}
		else
		{
			p.setPen(QPen(Qt::black, 1, Qt::SolidLine));
			p.drawLine(center(0, i), center(4, i));
			p.drawLine(center(5, i), center(9, i));
		}
	}
}

QPoint chess1::center(int row, int col)
{
	QPoint pt(_r * col * 2, _r * row * 2);
	return pt + _off;
}

QPoint chess1::center(int id)
{
	return center(_s[id]._row, _s[id]._col);
}

QPoint chess1::topLeft(int row, int col)
{
	return center(row, col) - QPoint(_r, _r);
}

QPoint chess1::topLeft(int id)
{
	return center(id) - QPoint(_r, _r);
}

QRect chess1::cell(int row, int col)
{
	return QRect(topLeft(row, col), QSize(_r * 2 - 1, _r * 2 - 1));
}

QRect chess1::cell(int id)
{
	return QRect(topLeft(id), QSize(_r * 2 - 1, _r * 2 - 1));
}

bool chess1::getClickRowCol(QPoint pt, int& row, int& col)
{
	for (row = 0; row <= 9; ++row)
	{
		for (col = 0; col <= 8; ++col)
		{
			QPoint distance = center(row, col) - pt;
			if (distance.x() * distance.x() + distance.y() * distance.y() < _r * _r)
				return true;
		}
	}
	return false;
}

void chess1::mouseReleaseEvent(QMouseEvent* ev)
{
	if (ev->button() != Qt::LeftButton)
	{
		return;
	}

	click(ev->pos());
}

bool chess1::canSelect(int id)
{
	return _bRedTurn == _s[id]._red;
}

void chess1::trySelectStone(int id)
{
	if (id == -1)
		return;

	if (!canSelect(id)) return;

	_selectid = id;
	update();
}

bool chess1::sameColor(int id1, int id2)
{
	if (id1 == -1 || id2 == -1) return false;

	return red(id1) == red(id2);
}

void chess1::tryMoveStone(int killid, int row, int col)
{
	if (killid != -1 && sameColor(killid, _selectid))
	{
		trySelectStone(killid);
		return;
	}

	bool ret = canMove(_selectid, killid, row, col);
	if (ret)
	{
		moveStone(_selectid, killid, row, col);
		_selectid = -1;
		update();
	}
}

int chess1::getStoneCountAtLine(int row1, int col1, int row2, int col2)
{
	int ret = 0;
	if (row1 != row2 && col1 != col2)
		return -1;
	if (row1 == row2 && col1 == col2)
		return -1;

	if (row1 == row2)
	{
		int min = col1 < col2 ? col1 : col2;
		int max = col1 < col2 ? col2 : col1;
		for (int col = min + 1; col < max; ++col)
		{
			if (getStoneId(row1, col) != -1) ++ret;
		}
	}
	else
	{
		int min = row1 < row2 ? row1 : row2;
		int max = row1 < row2 ? row2 : row1;
		for (int row = min + 1; row < max; ++row)
		{
			if (getStoneId(row, col1) != -1) ++ret;
		}
	}

	return ret;
}

int chess1::relation(int row1, int col1, int row, int col)
{
	return qAbs(row1 - row) * 10 + qAbs(col1 - col);
}

bool chess1::canMoveChe(int moveid, int, int row, int col)
{
	GetRowCol(row1, col1, moveid);
	int ret = getStoneCountAtLine(row1, col1, row, col);
	if (ret == 0)
		return true;
	return false;
}

bool chess1::canMoveMa(int moveid, int, int row, int col)
{
	GetRowCol(row1, col1, moveid);
	int r = relation(row1, col1, row, col);
	if (r != 12 && r != 21)
		return false;

	if (r == 12)
	{
		if (getStoneId(row1, (col + col1) / 2) != -1)
			return false;
	}
	else
	{
		if (getStoneId((row + row1) / 2, col1) != -1)
			return false;
	}

	return true;
}

bool chess1::canMovePao(int moveid, int killid, int row, int col)
{
	GetRowCol(row1, col1, moveid);
	int ret = getStoneCountAtLine(row, col, row1, col1);
	if (killid != -1)
	{
		if (ret == 1) return true;
	}
	else
	{
		if (ret == 0) return true;
	}
	return false;
}

bool chess1::canMoveBing(int moveid, int, int row, int col)
{
	GetRowCol(row1, col1, moveid);
	int r = relation(row1, col1, row, col);
	if (r != 1 && r != 10) return false;

	if (isBottomSide(moveid))
	{
		if (row > row1) return false;
		if (row1 >= 5 && row == row1) return false;
	}
	else
	{
		if (row < row1) return false;
		if (row1 <= 4 && row == row1) return false;
	}

	return true;
}

bool chess1::canMoveJiang(int moveid, int killid, int row, int col)
{
	if (killid != -1 && _s[killid]._type == Stone::JIANG)
		return canMoveChe(moveid, killid, row, col);

	GetRowCol(row1, col1, moveid);
	int r = relation(row1, col1, row, col);
	if (r != 1 && r != 10) return false;

	if (col < 3 || col > 5) return false;
	if (isBottomSide(moveid))
	{
		if (row < 7) return false;
	}
	else
	{
		if (row > 2) return false;
	}
	return true;
}

bool chess1::canMoveShi(int moveid, int, int row, int col)
{
	GetRowCol(row1, col1, moveid);
	int r = relation(row1, col1, row, col);
	if (r != 11) return false;

	if (col < 3 || col > 5) return false;
	if (isBottomSide(moveid))
	{
		if (row < 7) return false;
	}
	else
	{
		if (row > 2) return false;
	}
	return true;
}

bool chess1::canMoveXiang(int moveid, int, int row, int col)
{
	GetRowCol(row1, col1, moveid);
	int r = relation(row1, col1, row, col);
	if (r != 22) return false;

	int rEye = (row + row1) / 2;
	int cEye = (col + col1) / 2;
	if (getStoneId(rEye, cEye) != -1)
		return false;

	if (isBottomSide(moveid))
	{
		if (row < 4) return false;
	}
	else
	{
		if (row > 5) return false;
	}
	return true;
}

bool chess1::canMove(int moveid, int killid, int row, int col)
{
	if (sameColor(moveid, killid)) return false;

	switch (_s[moveid]._type)
	{
	case Stone::CHE:
		return canMoveChe(moveid, killid, row, col);

	case Stone::MA:
		return canMoveMa(moveid, killid, row, col);

	case Stone::PAO:
		return canMovePao(moveid, killid, row, col);

	case Stone::BING:
		return canMoveBing(moveid, killid, row, col);

	case Stone::JIANG:
		return canMoveJiang(moveid, killid, row, col);

	case Stone::SHI:
		return canMoveShi(moveid, killid, row, col);

	case Stone::XIANG:
		return canMoveXiang(moveid, killid, row, col);

	}
	return false;
}

void chess1::reliveStone(int id)
{
	if (id == -1) return;
	_s[id]._dead = false;
}

void chess1::killStone(int id)
{
	if (id == -1) return;
	_s[id]._dead = true;
}

bool chess1::isBottomSide(int id)
{
	return _bSide == _s[id]._red;
}

void chess1::moveStone(int moveid, int row, int col)
{
	_s[moveid]._row = row;
	_s[moveid]._col = col;

	_bRedTurn = !_bRedTurn;
}

void chess1::saveStep(int moveid, int killid, int row, int col, QVector<Step*>& steps)
{
	GetRowCol(row1, col1, moveid);
	Step* step = new Step;
	step->_colFrom = col1;
	step->_colTo = col;
	step->_rowFrom = row1;
	step->_rowTo = row;
	step->_moveid = moveid;
	step->_killid = killid;

	steps.append(step);
}

void chess1::moveStone(int moveid, int killid, int row, int col)
{
	saveStep(moveid, killid, row, col, _steps);

	killStone(killid);
	moveStone(moveid, row, col);
}

void chess1::click(int id, int row, int col)
{
	if (this->_selectid == -1)
	{
		trySelectStone(id);
	}
	else
	{
		tryMoveStone(id, row, col);
	}
}

void chess1::click(QPoint pt)
{
	int row, col;
	bool bClicked = getClickRowCol(pt, row, col);
	if (!bClicked) return;

	int id = getStoneId(row, col);
	click(id, row, col);
}

int chess1::getStoneId(int row, int col)
{
	for (int i = 0; i < 32; ++i)
	{
		if (_s[i]._row == row && _s[i]._col == col && !isDead(i))
			return i;
	}
	return -1;
}

void chess1::back(Step* step)
{
	reliveStone(step->_killid);
	moveStone(step->_moveid, step->_rowFrom, step->_colFrom);
}

void chess1::backOne()
{
	if (this->_steps.size() == 0) return;

	Step* step = this->_steps.last();
	_steps.removeLast();
	back(step);

	update();
	delete step;
}

void chess1::back()
{
	backOne();
}

void chess1::slotBack()
{
	back();
}
