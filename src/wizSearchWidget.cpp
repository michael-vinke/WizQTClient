#include "wizSearchWidget.h"

#ifdef Q_OS_MAC
#include "mac/wizSearchWidget_mm.h"
#else
#include "share/wizsettings.h"
#include "wizdef.h"

CWizSearchWidget::CWizSearchWidget(QWidget* parent /* = 0 */)
    : QWidget(parent)
    , m_widthHint(360)
{
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setSizePolicy(sizePolicy);
    setContentsMargins(1, 1, 1, 1);

    //QIcon icon = ::WizLoadSkinIcon(app.userSettings().skin(), palette().window().color(), "search");
    QLabel* iconLabel = new QLabel(this);
    //iconLabel->setPixmap(icon.pixmap(16, 16));
    iconLabel->setStyleSheet("QLabel{border-width:0;border-style:outset}");

    m_editSearch = new QLineEdit(this);
    m_editSearch->setTextMargins(5, 0, 0, 0);
    m_editSearch->setStyleSheet("QLineEdit{border:1px solid #aeaeae; border-radius:10px;}");

    // avoid focus rect on OSX, this should be a bug of qt style sheet
    m_editSearch->setAttribute(Qt::WA_MacShowFocusRect, 0);

    QHBoxLayout* layout = new QHBoxLayout(this);
    setLayout(layout);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    //layout->addWidget(iconLabel);
    layout->addWidget(m_editSearch);
    layout->setStretch(1, 1);

    connect(m_editSearch, SIGNAL(returnPressed()), \
            SLOT(on_search_returnPressed()));
}

void CWizSearchWidget::clear()
{
    m_editSearch->clear();
}

void CWizSearchWidget::focus()
{
    m_editSearch->selectAll();
    m_editSearch->setFocus();
}

QSize CWizSearchWidget::sizeHint() const
{
    return QSize(m_widthHint, height());
}

void CWizSearchWidget::setWidthHint(int nWidth)
{
    m_widthHint = nWidth;
}

void CWizSearchWidget::on_search_returnPressed()
{
    Q_EMIT doSearch(m_editSearch->text());
}

#endif // Q_OS_MAC

