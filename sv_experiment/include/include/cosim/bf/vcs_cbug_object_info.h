#ifndef VCS_CBUG_OBJECT_INFO_H
#define VCS_CBUG_OBJECT_INFO_H

#include "sysc/datatypes/int/sc_nbdefs.h"
//#include "sysc/kernel/sc_attribute.h"
#include "sysc/kernel/sc_object.h"
#include "sysc/utils/sc_string.h"
#include "vcs_cbug_streaming.h"
#include "sysc/communication/sc_prim_channel.h"


#if SYSTEMC_VERSION >= 20110630 && !defined(SC_23)
#define SC_23
#endif

#include <stdio.h>
#include <string.h>
#ifdef SC_23
#include <vector>
#endif
#include <set>
#include <vector>

class BfObject;

namespace sc_snps {

void vcs_cbug_event_dump( ::std::ostream& S, const sc_core::sc_event& E, const char* config );  
void vcs_cbug_attach_object_info_for_signal(sc_core::sc_object *scobj);
void vcs_cbug_attach_object_info_for_fifo(sc_core::sc_object *scobj);
class vcs_cbug_object_info;
vcs_cbug_object_info* vcs_cbug_get_object_attr(sc_core::sc_object *obj);
vcs_cbug_object_info* vcs_cbug_get_object_info_for_type(const char* type, void* pValue);



//
// vcs_cbug_object_info
//

class vcs_cbug_object_info : public sc_core::sc_attr_base {
    friend class sc_object;
public:
    vcs_cbug_object_info(const std::string &name, size_t sz);
    virtual ~vcs_cbug_object_info();

    virtual const char *show_value() const;
    virtual const char *show_value_slice(char radix, int highRange, int lowRange, int maxRange) const;
    virtual bool set_value(const char *string_value) const;

    virtual vcs_cbug_stream_object_base *attach_probe(std::string *errmsg);

    virtual const char *get_data_type_info() const;

    virtual std::string get_element_value(int element_index) const;
    virtual void addVPDScope(void *vpdscope);
    virtual void clearVPDScopes();

    virtual void save_content();

    virtual void *get_type_ptr() const
    {
        return 0;
    }
    size_t get_size_of_T() const
    {
        return size_of;
    }

protected:
    size_t size_of;

public:
#ifdef SC_23
    typedef std::vector<BfObject*> connect_vector;
#else
    typedef sc_core::sc_pvector<BfObject*> connect_vector;
#endif
    connect_vector m_BfConnectedObjects;
    void *hVPD_Scope;
};


class vcs_cbug_object_info_fifo_base : public vcs_cbug_object_info {
public:
    vcs_cbug_object_info_fifo_base(const std::string &name, 
                              size_t sz,
			      int *msize,
                              int *m_ri, 
			      int *m_wi, 
			      int *m_free, 
			      int *m_num_readable, 
			      int *m_num_read, 
			      int *m_num_written,
                              sc_core::sc_event* m_data_written_event,
                              sc_core::sc_event* m_data_read_event);
    virtual ~vcs_cbug_object_info_fifo_base();

    void get_fifo_status(int* pSize, int* pRi, int* pWi,
            int* pFree, int* pNumReadable, int* pNumRead, int* pNumWritten,
            bool* pIsTlmFifo)
    {
        if (pSize)
            *pSize = *m_size;
        if (pRi)
            *pRi = *m_ri;
        if (pWi)
            *pWi = *m_wi;
        if (pFree)
            *pFree = *m_free;
        if (pNumReadable)
            *pNumReadable = *m_num_readable;
        if (pNumRead)
            *pNumRead = *m_num_read;
        if (pNumWritten)
            *pNumWritten = *m_num_written;
        if (pIsTlmFifo)
            *pIsTlmFifo = m_isTlmFifo;
    }

    virtual void save_content_delayed(int reason);

    virtual vcs_cbug_stream_object_base *attach_probe(std::string *errmsg);

    static const std::vector<vcs_cbug_object_info_fifo_base*>& getAllFifoObjectInfos()
    {
        return m_allFifoObjectInfos;
    }

    virtual void pollUpdate();

protected:
    int *m_size;                 // logical size of the fifo buffer
    int *m_ri;                   // index of next read
    int *m_wi;                   // index of next write
    int *m_free;
    int *m_num_readable;         // #samples readable
    int *m_num_read;             // #samples read during this delta cycle
    int *m_num_written;          // #samples written during this delta cycle
    bool m_isTlmFifo;

    sc_core::sc_event* m_data_written_event;
    sc_core::sc_event* m_data_read_event;

    std::string m_dump;          // description of content used for VPD
    int m_dump_ctr;              // helper to avoid comparison:
                                 //  set when m_dump is written,
                                 //  reset when written into VPD
#ifdef SC_23
    std::vector<void*> vpdScopes;
#else
    sc_core::sc_pvector<void*> vpdScopes;
#endif

    static std::vector<vcs_cbug_object_info_fifo_base*> m_allFifoObjectInfos;
    struct bf_sc_fifo_ref* m_pRefFifo;
};


}  // sc_snps

#endif
