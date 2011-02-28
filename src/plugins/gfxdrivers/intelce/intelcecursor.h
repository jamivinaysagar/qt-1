
#ifndef INTELCECURSOR_H
#define INTELCECURSOR_H

#include <QtGui>
#include <QScreenCursor>

#ifndef QT_NO_QWS_CURSOR

class IntelCECursor : public QScreenCursor
{
  public:
	static void initCursor();
	static IntelCECursor* instance();

	        bool isAccelerated() const;

	virtual void show();
	virtual void hide();
	        bool isVisible() const;
	virtual void move(int x, int y);

	virtual void set(const QImage& image, int hotx, int hoty);
          QImage image() const;
		   QRect boundingRect() const;

  private:
	IntelCECursor();
	virtual ~IntelCECursor();

	QImage  m_image, m_bitmap;
	void*   m_pvCursor;
	bool    m_bVisible;
};
#endif

#endif // INTELCECURSOR_H
