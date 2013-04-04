//-----------------------------------------------------------------------------
//
// Xbox Matchmaking Definitions for Title: Jedi Academy [0x4C41000B]
// Generated by MatchSim
//
//-----------------------------------------------------------------------------
#pragma once


#include <xtl.h>
#include <xonline.h>
#include <assert.h>




//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------

//
// Attribute IDs                          ID num   Data Type
//                                        ------   ----------------------------
const DWORD XATTRIB_GAME_TYPE            = 0x0001 | X_ATTRIBUTE_DATATYPE_INTEGER;
const DWORD XATTRIB_CURRENT_MAP          = 0x0002 | X_ATTRIBUTE_DATATYPE_INTEGER;
const DWORD XATTRIB_SESSION_NAME         = 0x0003 | X_ATTRIBUTE_DATATYPE_STRING;
const DWORD XATTRIB_FRIENDLY_FIRE        = 0x0004 | X_ATTRIBUTE_DATATYPE_INTEGER;
const DWORD XATTRIB_JEDI_MASTERY         = 0x0005 | X_ATTRIBUTE_DATATYPE_INTEGER;
const DWORD XATTRIB_TOTAL_PLAYERS        = 0x0007 | X_ATTRIBUTE_DATATYPE_INTEGER;
const DWORD XATTRIB_SABER_ONLY           = 0x0008 | X_ATTRIBUTE_DATATYPE_INTEGER;
const DWORD XATTRIB_DEDICATED            = 0x0009 | X_ATTRIBUTE_DATATYPE_INTEGER;


//
// Attribute Maximum Lengths
// (for strings, this doesn't include the terminating NULL)
//
const DWORD XATTRIB_SESSION_NAME_MAX_LEN = 16; // SessionName attribute


// Specify X_MATCH_NULL_INTEGER for optional integer query arguments
const ULONGLONG X_MATCH_NULL_INTEGER  = 0x7FFFFFFFFFFFFFFFui64;

// Maximum number of sessions returned by OptiMatch query
const DWORD MAX_OPTI_MATCH_RESULTS = 25;

// Maximum number of sessions returned by JoinSessionByID query
const DWORD MAX_JOIN_SESSION_BY_ID_RESULTS = 1;

// Number of QoS probes
const DWORD NUM_QOS_PROBES   =     8;

// Maximum bandwidth to consume for QoS probes
const DWORD QOS_BITS_PER_SEC = 16000;





//-----------------------------------------------------------------------------
// Types
//-----------------------------------------------------------------------------

// Helper class for getting/setting blob attributes
class CBlob
{
public:
    CBlob() : m_wLength( 0 ), m_pvData( NULL ) {}
    CBlob( WORD wLength, const PVOID pvData ) : m_wLength( wLength), m_pvData( pvData) {}
    CBlob( const CBlob & b ) { *this = b; }
    CBlob & operator=( const CBlob & b ) 
    { m_wLength = b.Length; m_pvData = b.Data; return *this; }
    BOOL operator==( const CBlob & b ) const  
    { return m_wLength == b.Length && memcmp( m_pvData, b.Data, b.Length ) == 0; }
    BOOL IsNull() { return m_pvData == NULL; }
    __declspec( property( put = SetData, get=GetData ) ) const PVOID Data;
    const PVOID GetData() const { return m_pvData; }
    VOID SetData( const PVOID pvData ) { m_pvData = pvData; }
    __declspec( property( put = SetLength, get=GetLength ) ) WORD Length;
    WORD GetLength() const { return m_wLength; }
    VOID SetLength( WORD wLength ) { m_wLength = wLength; }
private:
    WORD m_wLength;
    PVOID m_pvData;
};

// A null blob is defined as having a NULL pointer
#define NULL_BLOB CBlob( 0, NULL )

// Macro for declaring "blob literals" (much like the _T() macro does for strings)
#define B( length, ptr ) CBlob( length, (const PVOID) ptr )

class CSession
{
public:
    CSession();
    ~CSession();

    HRESULT Create();
    HRESULT Update();
    HRESULT Delete();
    HRESULT Process();

    VOID    Reset();

    DWORD PublicFilled;
    DWORD PublicOpen;
    DWORD PrivateFilled;
    DWORD PrivateOpen;
    XNKEY KeyExchangeKey;
    XNKID SessionID;

    BOOL IsUpdating() const { return m_State == STATE_UPDATING; }
    BOOL IsDeleting() const { return m_State == STATE_DELETING; }
    BOOL IsCreating() const { return m_State == STATE_CREATING; }
    BOOL Exists()     const { return m_State == STATE_ACTIVE || IsUpdating(); }

    // Attribute Accessors

    BOOL IsListening() const { return m_bListening; }
    __declspec( property( put = SetQosResponse, get = GetQosResponse ) ) CBlob QosResponse;
    CBlob GetQosResponse();
    VOID SetQosResponse( CBlob Value );
    VOID Listen( BOOL bEnable = TRUE, DWORD dwBitsPerSec = 0 );
    static const DWORD NO_WAIT = 1;

    __declspec( property( put = SetGameType, get=GetGameType ) ) ULONGLONG GameType;
    ULONGLONG GetGameType();
    VOID SetGameType( ULONGLONG Value );

    __declspec( property( put = SetCurrentMap, get=GetCurrentMap ) ) ULONGLONG CurrentMap;
    ULONGLONG GetCurrentMap();
    VOID SetCurrentMap( ULONGLONG Value );

    __declspec( property( put = SetSessionName, get=GetSessionName ) ) const WCHAR * SessionName;
    const WCHAR * GetSessionName();
    VOID SetSessionName( const WCHAR * Value );

    __declspec( property( put = SetFriendlyFire, get=GetFriendlyFire ) ) ULONGLONG FriendlyFire;
    ULONGLONG GetFriendlyFire();
    VOID SetFriendlyFire( ULONGLONG Value );

    __declspec( property( put = SetJediMastery, get=GetJediMastery ) ) ULONGLONG JediMastery;
    ULONGLONG GetJediMastery();
    VOID SetJediMastery( ULONGLONG Value );

    __declspec( property( put = SetTotalPlayers, get=GetTotalPlayers ) ) ULONGLONG TotalPlayers;
    ULONGLONG GetTotalPlayers();
    VOID SetTotalPlayers( ULONGLONG Value );

    __declspec( property( put = SetSaberOnly, get=GetSaberOnly ) ) ULONGLONG SaberOnly;
    ULONGLONG GetSaberOnly();
    VOID SetSaberOnly( ULONGLONG Value );

    __declspec( property( put = SetDedicated, get=GetDedicated ) ) ULONGLONG Dedicated;
    ULONGLONG GetDedicated();
    VOID SetDedicated( ULONGLONG Value );

private:

    // The m_Attributes array is accessed using predefined constants:
    enum
    {
        GAME_TYPE_INDEX,
        CURRENT_MAP_INDEX,
        SESSION_NAME_INDEX,
        FRIENDLY_FIRE_INDEX,
        JEDI_MASTERY_INDEX,
        TOTAL_PLAYERS_INDEX,
        SABER_ONLY_INDEX,
        DEDICATED_INDEX,
        NUM_ATTRIBUTES
    };

    XONLINE_ATTRIBUTE m_Attributes[NUM_ATTRIBUTES];

    // Storage for the SessionName string attribute
    WCHAR m_strSessionName[XATTRIB_SESSION_NAME_MAX_LEN+1];


    // Qos listening
    struct QosQEntry
    {
        XNKID  SessionID;            // Session to unregister
        DWORD  dwStartTick;          // Time entry was added
        struct QosQEntry *pNext;     // Next item in the queue
    };
    class CSessionQosQ
    {
    public:
        CSessionQosQ();
        VOID Add( XNKID & SessionID, DWORD dwStartTick );
        VOID Remove( XNKID &SessionID );
        VOID Dequeue();
        const QosQEntry *Head() const { return m_pHead; }
        const QosQEntry *Tail() const { return m_pTail; }
    private:

        QosQEntry *m_pHead;
        QosQEntry *m_pTail;
    };

    CSessionQosQ m_SessionQosQ;
    BOOL  m_bListening;              // Listening for Qos probes
    CBlob m_QosResponse;
    VOID  PurgeSessionQ( BOOL fRemoveAll = FALSE );
    VOID  PurgeSessionQHead();



    HRESULT ProcessStateCreateSession();
    HRESULT ProcessStateUpdateSession();
    HRESULT ProcessStateDeleteSession();
    HRESULT ProcessStateActiveSession();

    VOID    Close();
    VOID    SetupAttributes();

    XONLINETASK_HANDLE m_hSessionTask;

    enum STATE
    {
        STATE_IDLE,
        STATE_CREATING,
        STATE_UPDATING,
        STATE_DELETING,
        STATE_ACTIVE
    };

    STATE m_State;
    BOOL  m_bKeyRegistered;
    BOOL  m_bUpdate;

};




//
// COptiMatchResult represents a single return result from the
// OptiMatch query
//
#pragma pack(push, 1)
class COptiMatchResult
{
public:
    // The query return attributes must come first, and in the order
    // returned by the query
    ULONGLONG GameType;
    ULONGLONG CurrentMap;
    WCHAR     SessionName[XATTRIB_SESSION_NAME_MAX_LEN+1];
    ULONGLONG FriendlyFire;
    ULONGLONG JediMastery;
    ULONGLONG SaberOnly;
    ULONGLONG Dedicated;


    XNKID      SessionID;
    XNKEY      KeyExchangeKey;
    XNADDR     HostAddress;
    DWORD      PublicOpen;
    DWORD      PrivateOpen;
    DWORD      PublicFilled;
    DWORD      PrivateFilled;
    XNQOSINFO* pQosInfo;

};
#pragma pack(pop)



//  Collection of results for the OptiMatch query
class COptiMatchQueryResults
{
public:
    COptiMatchQueryResults() { m_dwSize = 0; }
    DWORD Size() { return m_dwSize; }
    COptiMatchResult &operator[]( DWORD i ) { return v[i]; }
private:
    void Clear() { m_dwSize = 0; }
    void Remove( DWORD i )
    {
        assert( i < m_dwSize );
        if( i < m_dwSize )
        {
            m_dwSize--;
            memcpy( &v[i], &v[i+1], sizeof( v[0] ) * ( m_dwSize - i ) );
        }
    }
    void SetSize( DWORD dwSize ) { m_dwSize = dwSize; }
    friend class COptiMatchQuery;
    COptiMatchResult v[MAX_OPTI_MATCH_RESULTS];
    DWORD m_dwSize;
};



//
// Query object for OptiMatch query (id 0x1)
//
class COptiMatchQuery
{
public:
    COptiMatchQuery();
    ~COptiMatchQuery();
    COptiMatchQueryResults Results;

    HRESULT Process();
    void Cancel();
    void Clear();
    BOOL Done()      const { return m_State == STATE_DONE; }
    BOOL Succeeded() const { return SUCCEEDED( m_hrQuery ); }
    HRESULT Query(
                  ULONGLONG GameType, // Optional: X_MATCH_NULL_INTEGER to omit
                  ULONGLONG CurrentMap, // Optional: X_MATCH_NULL_INTEGER to omit
                  ULONGLONG MinimumPlayers,
                  ULONGLONG MaximumPlayers,
                  ULONGLONG FriendlyFire, // Optional: X_MATCH_NULL_INTEGER to omit
                  ULONGLONG JediMastery, // Optional: X_MATCH_NULL_INTEGER to omit
                  ULONGLONG SaberOnly, // Optional: X_MATCH_NULL_INTEGER to omit
                  ULONGLONG Dedicated // Optional: X_MATCH_NULL_INTEGER to omit
                 );
    BOOL IsRunning() const { return m_State == STATE_RUNNING || m_State == STATE_PROBING_CONNECTIVITY; }
    BOOL IsProbing() const { return m_State == STATE_PROBING_BANDWIDTH; }
    HRESULT Probe();
private:

    // Quality of Service
    const XNADDR *m_rgpXnAddr[ MAX_OPTI_MATCH_RESULTS ];
    const XNKID  *m_rgpXnKid [ MAX_OPTI_MATCH_RESULTS ];
    const XNKEY  *m_rgpXnKey [ MAX_OPTI_MATCH_RESULTS ];
    XNQOS  *m_pXnQos;
    enum STATE
    {
        STATE_IDLE,
        STATE_RUNNING,
        STATE_PROBING_CONNECTIVITY,
        STATE_PROBING_BANDWIDTH,
        STATE_DONE
    };

    STATE m_State;
    HRESULT m_hrQuery;
    XONLINETASK_HANDLE m_hSearchTask;
};




//
// CJoinSessionByIDResult represents a single return result from the
// JoinSessionByID query
//
#pragma pack(push, 1)
class CJoinSessionByIDResult
{
public:

    XNKID      SessionID;
    XNKEY      KeyExchangeKey;
    XNADDR     HostAddress;
    DWORD      PublicOpen;
    DWORD      PrivateOpen;
    DWORD      PublicFilled;
    DWORD      PrivateFilled;
    XNQOSINFO* pQosInfo;

};
#pragma pack(pop)



//  Collection of results for the JoinSessionByID query
class CJoinSessionByIDQueryResults
{
public:
    CJoinSessionByIDQueryResults() { m_dwSize = 0; }
    DWORD Size() { return m_dwSize; }
    CJoinSessionByIDResult &operator[]( DWORD i ) { return v[i]; }
private:
    void Clear() { m_dwSize = 0; }
    void Remove( DWORD i )
    {
        assert( i < m_dwSize );
        if( i < m_dwSize )
        {
            m_dwSize--;
            memcpy( &v[i], &v[i+1], sizeof( v[0] ) * ( m_dwSize - i ) );
        }
    }
    void SetSize( DWORD dwSize ) { m_dwSize = dwSize; }
    friend class CJoinSessionByIDQuery;
    CJoinSessionByIDResult v[MAX_JOIN_SESSION_BY_ID_RESULTS];
    DWORD m_dwSize;
};



//
// Query object for JoinSessionByID query (id 0x2)
//
class CJoinSessionByIDQuery
{
public:
    CJoinSessionByIDQuery();
    ~CJoinSessionByIDQuery();
    CJoinSessionByIDQueryResults Results;

    HRESULT Process();
    void Cancel();
    void Clear();
    BOOL Done()      const { return m_State == STATE_DONE; }
    BOOL Succeeded() const { return SUCCEEDED( m_hrQuery ); }
    HRESULT Query(
                  ULONGLONG SessionID
                 );
    BOOL IsRunning() const { return m_State == STATE_RUNNING || m_State == STATE_PROBING_CONNECTIVITY; }
    BOOL IsProbing() const { return m_State == STATE_PROBING_BANDWIDTH; }
    HRESULT Probe();
private:

    // Quality of Service
    const XNADDR *m_rgpXnAddr[ MAX_JOIN_SESSION_BY_ID_RESULTS ];
    const XNKID  *m_rgpXnKid [ MAX_JOIN_SESSION_BY_ID_RESULTS ];
    const XNKEY  *m_rgpXnKey [ MAX_JOIN_SESSION_BY_ID_RESULTS ];
    XNQOS  *m_pXnQos;
    enum STATE
    {
        STATE_IDLE,
        STATE_RUNNING,
        STATE_PROBING_CONNECTIVITY,
        STATE_PROBING_BANDWIDTH,
        STATE_DONE
    };

    STATE m_State;
    HRESULT m_hrQuery;
    XONLINETASK_HANDLE m_hSearchTask;
};