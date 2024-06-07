#include <QStringList>
#include <QMessageBox>
#include <QTimer>
#include <QHeaderView>
#include <QFile>


#include <QStyledItemDelegate>
#include <QPainter>

class RoundedItemDelegate : public QStyledItemDelegate {
public:
    RoundedItemDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        painter->save();
        
        QRect rect = option.rect;
        painter->setRenderHint(QPainter::Antialiasing, true);

        QString text = index.data().toString();
        
        QColor backgroundColor;

        if (text == "Block") {   // block button
            backgroundColor = QColor("#EC133D"); // red
        } else if (text == "Unblock") {   // unblock button
            backgroundColor = QColor("#25BF58"); // green
        } else if (text == "X") {   // delete button
            backgroundColor = QColor(0, 0, 0);
        } else if (!index.data(Qt::UserRole).toBool()) {  // all the cells of a device that is not remembered
            backgroundColor = QColor(220, 220, 220);
        } else {
            backgroundColor = (option.state & QStyle::State_Selected) ? QColor("#b0c4de") : QColor("#f9f9f9");
        }
        painter->setBrush(backgroundColor);

        painter->setPen(Qt::NoPen);
        if(text == "Block" || text == "Unblock" || text == "X")
            painter->drawRoundedRect(rect.adjusted(1, 1, -1, -1), 10, 10); 
        else
            painter->drawRoundedRect(rect.adjusted(1, 1, -1, -1), 1, 1); 
        
        QStyledItemDelegate::paint(painter, option, index);
        painter->restore();
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        return QStyledItemDelegate::sizeHint(option, index);
    }
};