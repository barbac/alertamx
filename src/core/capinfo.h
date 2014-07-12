#pragma once

#include <QObject>

class CategoryGadget {
    Q_GADGET
    Q_ENUMS(Category)

public:
    enum class Category
    {
        Geo,       // Geophysical (inc. landslide)
        Met,       // Meteorological (inc. flood)
        Safety,    // General emergency and public safety
        Security,  // Law enforcement, military, homeland and local/private
                   // security
        Rescue,    // Rescue and recovery
        Fire,      // Fire suppression and rescue
        Health,    // Medical and public health
        Env,       // Pollution and other environmental
        Transport, // Public and private transportation
        Infra,     // Utility, telecommunication, other non-transport
                   // infrastructure
        CBRNE,     // Chemical, Biological, Radiological, Nuclear or
                   // High-Yield Explosive threat or attack
        Other,     // Other events
    };
};
typedef CategoryGadget::Category Category;

class ResponseTypeGadget {
    Q_GADGET
    Q_ENUMS(ResponseType)

public:
    enum class ResponseType
    {
        Shelter,  // Take shelter in place or per <instruction>
        Evacuate, // Relocate as instructed in the <instruction>
        Prepare,  // Make preparations per the <instruction>
        Execute,  // Execute a pre-planned activity identified in <instruction>
        Avoid,    // Avoid the subject event as per the <instruction>
        Monitor,  // Attend to information sources as described in <instruction>
        Assess,   // Evaluate the information in this message. (This value
                  // SHOULD NOT be used in public warning applications.)
        AllClear, // The subject event no longer poses a threat or concern and
                  // any follow on action is described in <instruction>
        None,     // No action recommended
    };
};
typedef ResponseTypeGadget::ResponseType ResponseType;


class UrgencyGadget {
    Q_GADGET
    Q_ENUMS(Urgency)

public:
    enum class Urgency {
        Immediate, // Responsive action SHOULD be taken immediately
        Expected,  // Responsive action SHOULD be taken soon (within next hour)
        Future,    // Responsive action SHOULD be taken in the near future
        Past,      // Responsive action is no longer required
        Unknown,   // Urgency not known
    };
};
typedef UrgencyGadget::Urgency Urgency;

class SeverityGadget {
    Q_GADGET
    Q_ENUMS(Severity)

public:
    enum class Severity {
        Extreme,  // Extraordinary threat to life or property
        Severe,   // Significant threat to life or property
        Moderate, // Possible threat to life or property
        Minor,    // Minimal to no known threat to life or property
        Unknown,  // Severity unknown
    };
};
typedef SeverityGadget::Severity Severity;

class CertaintyGadget {
    Q_GADGET
    Q_ENUMS(Certainty)

public:
    enum class Certainty {
        Observed, // Determined to have occurred or to be ongoing
        Likely,   // Likely (p > ~50%)
        Possible, // Possible but not likely (p <= ~50%)
        Unlikely, // Not expected to occur (p ~ 0)
        Unknown,  // Certainty unknown
    };
};
typedef CertaintyGadget::Certainty Certainty;


class CAPInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString language NOTIFY languageChanged MEMBER m_language)
    Q_PROPERTY(Category category READ category WRITE setCategory
               NOTIFY categoryChanged)
    Q_PROPERTY(QString categoryString READ categoryString CONSTANT)
    Q_PROPERTY(QString event NOTIFY eventChanged MEMBER m_event)
    Q_PROPERTY(ResponseType responseType NOTIFY responseTypeChanged MEMBER m_responseType)
    Q_PROPERTY(Urgency urgency NOTIFY urgencyChanged MEMBER m_urgency)
    Q_PROPERTY(Severity severity NOTIFY severityChanged MEMBER m_severity)
    Q_PROPERTY(Certainty certainty NOTIFY certaintyChanged MEMBER m_certainty)
    //Q_PROPERTY(QString audience NOTIFY audienceChanged MEMBER m_audience)
    //eventCode
    Q_PROPERTY(QString effective NOTIFY effectiveChanged MEMBER m_effective)
    //Q_PROPERTY(QString onset NOTIFY onsetChanged MEMBER m_onset)
    Q_PROPERTY(QString expires NOTIFY expiresChanged MEMBER m_expires)
    Q_PROPERTY(QString senderName NOTIFY senderNameChanged MEMBER m_senderName)
    Q_PROPERTY(QString headline NOTIFY headlineChanged MEMBER m_headline)
    Q_PROPERTY(QString description NOTIFY descriptionChanged MEMBER m_description)
    Q_PROPERTY(QString instruction NOTIFY instructionChanged MEMBER m_instruction)
    Q_PROPERTY(QString web NOTIFY webChanged MEMBER m_web)
    Q_PROPERTY(QString contact NOTIFY contactChanged MEMBER m_contact)
    //parameters;
    //area

signals:
    void languageChanged();
    void categoryChanged(Category);
    void eventChanged();
    void responseTypeChanged();
    void urgencyChanged();
    void severityChanged();
    void certaintyChanged();
    //void audienceChanged();
    //eventCode
    void effectiveChanged();
    //void onsetChanged();
    void expiresChanged();
    void senderNameChanged();
    void headlineChanged();
    void descriptionChanged();
    void instructionChanged();
    void webChanged();
    void contactChanged();
    //parameters;
    //area

public slots:
    void setCategory(Category category);

public:
    explicit CAPInfo(QObject *parent);
    Category category() const;
    QString categoryString() const;

    QString m_language;
    //TODO: find out what exactly does this means:
    //(2)   Multiple instances MAY occur within an <info> block.
    Category m_category;
    QString m_event;
    //TODO: find out what exactly does this means:
    //(2)   Multiple instances MAY occur within an <info> block.
    ResponseType m_responseType;
    Urgency m_urgency;
    Severity m_severity;
    //(3) For backward compatibility with CAP 1.0, the deprecated value of
    //“Very Likely” SHOULD be treated as equivalent to “Likely”.
    Certainty m_certainty;
    //QString m_audience;
    //eventCode
    QString m_effective;
    //QString m_onset;
    QString m_expires;
    QString m_senderName;
    QString m_headline;
    QString m_description;
    QString m_instruction;
    QString m_web;
    QString m_contact;
    //parameters;
    //area
};
