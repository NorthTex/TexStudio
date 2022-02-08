#ifndef Header_Template_Manager
#define Header_Template_Manager


#include "mostQtHeaders.h"


class Template;
class TemplateSelector;


class TemplateHandle {

	public:

		friend class Template;

		TemplateHandle() : m_tmpl(nullptr) {}
		TemplateHandle(const TemplateHandle &);
		explicit TemplateHandle(Template *);
		~TemplateHandle();

		TemplateHandle &operator = (const TemplateHandle &th);

		bool isValid() const;
		QString name() const;
		QString description() const;
		QString author() const;
		QString version() const;
		QDate date() const;
		QString license() const;
		QPixmap previewImage() const;
		QString file() const;
		bool isEditable() const;
		bool isMultifile() const;
		bool createInFolder(const QString & path) const;
		QStringList filesToOpen() const;

	private:

		void setTmpl(Template *tmpl);
		Template *m_tmpl;  // only write via setTmpl()

};

Q_DECLARE_METATYPE( TemplateHandle )


class AbstractTemplateResource {

	public:

		virtual QList<TemplateHandle> getTemplates() = 0;
		virtual bool isAccessible() = 0;
		virtual QString name() = 0;
		virtual QString description() = 0;
		virtual QIcon icon() = 0;

	protected:

		AbstractTemplateResource() {}
};

Q_DECLARE_INTERFACE( AbstractTemplateResource , "TeXstudio/AbstractTemplateResource")
Q_DECLARE_METATYPE( AbstractTemplateResource * )


class TemplateManager : public QObject {

	Q_OBJECT

	public:

		explicit TemplateManager(QObject * parent = nullptr);

        static void setConfigBaseDir(const QString & dir){
            configBaseDir = dir;
        }

        static QString userTemplateDir(){
            return configBaseDir + "templates/user/";
        }

        static QString builtinTemplateDir();
        static bool ensureUserTemplateDirExists();
        static void checkForOldUserTemplates();

        AbstractTemplateResource * createResourceFromXMLNode(const QDomElement & resElem);
        QList<AbstractTemplateResource *> resourcesFromXMLFile(const QString & filename);
        TemplateSelector * createLatexTemplateDialog();
        bool tableTemplateDialogExec();

        QString selectedTemplateFile(){
            return selectedFile;
        }

    signals:

        void editRequested(const QString & filename);

    private slots:

        void editTemplate(TemplateHandle);
        void editTemplateInfo(TemplateHandle);

    private:

        static QString configBaseDir;
        QString selectedFile;

};

#endif