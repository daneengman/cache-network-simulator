#ifndef __VCS_DESIGN_H
#define __VCS_DESIGN_H
// This VcsDesign file contains C based callbacks for the babelfish
// code to call during initialization.
// It also contains the C++ based class, VcsDesign, which is a
// representation of the Vcs simulation's design.  As the SystemC
// models are created, they are "registered" with the class for
// use by the Vcs simulator.
// Verilog modules that you'll find registered with this class
// are those that have a generated SystemC interface wrapper for
// them.  All other Verilog modules are implicitily called through
// those that have a respective SystemC interface model.


#include "systemc.h"
#include "systemc_user.h"

#include <string>
#include <vector>
#include <iostream>

class VcsDesign;
class BfModule;

typedef int (*DesignMainFunc)(int, char**);
typedef void (*ODesignMainFunc)(int, char **);


class VcsParam {
public:
    enum ParamType { HDL_INTEGER, HDL_REAL, HDL_STRING, HDL_UNSUPPORTED };

public:
    VcsParam(std::string name, ParamType type, std::string value) :
        _name(name),
        _type(type),
        _value(value) {}

    std::string getParam() const
    {
        std::string param = "." + _name + "(" + _value + ")";
        return param;
    }
    const std::string getName() const {return _name;}
    const std::string getValue() const { return _value; }
    void _setValue(const std::string &val) { _value = val; }
#ifdef _SNPS_SCFE_
  protected:
#else
  private:
#endif
    std::string _name;
    ParamType _type;
    std::string _value;
};

// Type used to represent VCS port data.
static const char* delay_type_enum_str_tab[] =
{
    "VcsPort::BC_C",  // backward compatibility mode, 
    "VcsPort::NONE_C",
    "VcsPort::NBA_C",
    "VcsPort::ZERO_C"
};
class VcsPort {
public:
    enum PortType {INPUT_PORT, OUTPUT_PORT, INOUT_PORT};
    enum DelayType { BC_C = 0, NONE_C, NBA_C, ZERO_C };

public:
    VcsPort(std::string name, PortType type, int size, int array_size,
            std::string sc_type, DelayType delay_type)
        : _name(name) , _type(type), _size(size), _array(array_size), m_nr(-1),
        m_sc_type(sc_type), m_delay_type(delay_type) { }

    bool isInput() const  {return _type == INPUT_PORT;}
    bool isOutput() const {return _type == OUTPUT_PORT;}
    bool isInout() const  {return _type == INOUT_PORT;}
    const std::string getName() const {return _name;}
    const std::string getScType() const {return m_sc_type;}
    const DelayType getDelayType() const { return  m_delay_type;}
    const std::string getDelayTypeStr() const { return
        delay_type_enum_str_tab[m_delay_type];}

    int size() const {
        return _size;
    }

    int array_size() const {
        return _array;
    }

    void setInterface(int nr, const std::string &pname) {
        m_nr = nr;
        m_pname = pname;
    }
    int getNr() const { return m_nr; }
    const std::string &getAltName() const { return m_pname; }

#ifdef _SNPS_SCFE_
  protected:
#else
  private:
#endif
    std::string   _name;
    PortType _type;
    int   _size;
    int   _array;
    int m_nr;
    std::string m_sc_type;
    DelayType m_delay_type;
    std::string m_pname;
};

// Type used to represent VCS instance data.
class VcsInstance {
public:
    VcsInstance(std::string name) :
        _portList(),
        _name(name),
        _isVHDL(false),
        _mode(0),
        _scobj(0)  {}
    const std::string getName() const {return _name;}

    // Model port methods
    VcsPort* addPort(const std::string& port, VcsPort::PortType type, int size, int array_size,
                     const std::string& sc_type = "", VcsPort::DelayType delay_type = VcsPort::BC_C);
    VcsParam *addParameter(const std::string &param, VcsParam::ParamType type, const std::string &value);
    void setScObj(sc_core::sc_object *obj) { _scobj = obj; }
    sc_core::sc_object *getScObj() const { return _scobj; }
    void setNames(const std::string &iname, const std::string &nname, const std::string &bname)
    { m_iname = iname, m_nname = nname; m_bname = bname; }
    const std::string &getIname() const { return m_iname; }
    const std::string &getNname() const { return m_nname; }
    const std::string &getBname() const { return m_bname; }
    int getPortCount() const { return _portList.size(); }
    int getInputPortCount() const;
    int getInoutPortCount() const;
    int getOutputPortCount() const;
    int getOutputPortCountArray() const;
    int getParameterCount() const { return _paramList.size(); }
    const VcsParam* getParam(int i) const { return _paramList[i]; }
    const VcsPort* getPort(int i) const { return _portList[i]; }
    VcsPort* getPort(int i) { return _portList[i]; }
    void setVHDL() { _isVHDL = true; }
    bool isVHDL() const { return _isVHDL; }
    VcsParam *getParameter(const std::string &);
    void setMode(int mode) { _mode = mode; }
    int getMode() const { return _mode; }
#ifdef _SNPS_SCFE_
  protected:
#else
  private:
#endif
    std::vector<VcsPort*> _portList;
    std::vector<VcsParam*> _paramList;
    std::string _name;
    bool _isVHDL;
    int _mode;
    sc_core::sc_object *_scobj;
    std::string m_iname;
    std::string m_nname;
    std::string m_bname;
};

// Type used to represent VCS model data.
class VcsModel {
public:
    VcsModel(std::string name) : _instanceList() , _name(name), _isVHDL(false) {}

    const std::string getName() const {return _name;}

    // Model instance methods.
    VcsInstance* addInstance(const std::string& instance);
    int getInstanceCount() const { return _instanceList.size(); }
    VcsInstance* getInstance(int i) const { return _instanceList[i]; }
    const std::vector<VcsInstance*>& getInstanceList() const { return _instanceList; }
    ostream& generateUglyInoutCode(ostream& s) const;
    bool containsInoutPorts() const;
    void setVHDL() { _isVHDL = true; }
    bool isVHDL() const { return _isVHDL; }

    VcsParam *getParameter(const std::string &);
#ifdef _SNPS_SCFE_
  protected:
#else
  private:
#endif
    std::vector<VcsInstance*> _instanceList;
    std::string _name;
    bool _isVHDL;
};

/**
 * The VcsDesign object represents all the Verilog modules in the
 * design that are instantiated from a SystemC model.  This does
 * not include those Verilog modules that are instantiated by a
 * Verilog module.
 */
class VcsDesign {
public:
    struct Def {
        Def(std::string name, std::string file) : _name(name), _file(file) {}
        std::string _name;
        std::string _file;
    };
    struct Obj {
        Obj(std::string file, std::string obj) : _file(file), _obj(obj) {}
        std::string _file;
        std::string _obj;
    };

protected:
    // Construct a design without a design name.
    VcsDesign()
        : _topFile("vcs/top.v")
        , _modelList()
        , _argsList()
        , _name("simv")
        , _cosimLib("")
        , _mainFunc(NULL)
        , _omainFunc(NULL)
        , _isVcsInitialized(false)
        , _vdefList()
        , _sdefList()
        , _objList()
        , _isVHDL(false)
        , _pid("")
        , errorcnt(0)
    {
    }

public:
    static VcsDesign* getDesignInstance();
    std::string            getName() const {return _name;}
    std::string        getTopFile() const { return _topFile; }

    // Model methods
    VcsModel*         addModel(const std::string& model);
    int               getModelCount() const;
    const VcsModel*   getModel(int index) const;
    void              dumpTopVerilog();
    void              buildTopVerilog();
    void              openTopVerilog();
    void              setupArgs(int argc, char** argv);
    void              SimvMain();
    void              SimvMain_Init();
    void              elaborate(bool force_write_skeleton);
    void              elaborate_check();
    bool              isVcsInitialized() const;
    void              loadSystemCInfoFile();
    bool              containsInoutVectorPorts() const;
    bool              containsInoutScalarPorts() const;
    void              generateInoutVectorAdapter(ostream& s) const;
    void              generateInoutScalarAdapter(ostream& s) const;
    bool              isVHDL() const {return _isVHDL;}
    void              setVHDL() {_isVHDL = true;}
    std::string            getPID();

    void dumpFileTopDotV(ostream &);
    void dumpFileSyscSkeletonDotV(ostream &, bool);
    void dumpFileSyscSkeletonDotVmd5(const std::string &, std::string);
    void dumpFileC(ostream &);
    void dumpFileTab(ostream &);

    VcsParam *getParameter(const std::string &);

    /** The design top verilog file. */
    std::string             _topFile;

    void incrErrorCnt() { errorcnt++; }
#ifdef _SNPS_SCFE_
  protected:
#else
  private:
#endif
    std::string dumpRecurseSkeletonModules(ostream &s, const BfModule* obj, bool isTliFunFlow, bool);
    std::string dumpRecurseIfGenModule(ostream &s, const BfModule* obj, const char* sIfGenFile, bool TliFuncFlow, bool);
    int forkExecAndWait( const char* path, char** args);
    void resolveShowScMain();

    /** Our singleton for keeping all the Vcs modules. */
    static VcsDesign   *_instance;

    /** List of models. */
    std::vector<VcsModel*>  _modelList;

    /** List of arguments to the Vcs SimvMain routine. */
    std::vector<std::string*>    _argsList;

    /** The design name. */
    std::string             _name;


    /** The design library used by SystemC on top. */
    std::string             _cosimLib;

    /** A pointer to the SimvMain function. */
    DesignMainFunc     _mainFunc;

    ODesignMainFunc     _omainFunc;

    /** Has the verilog code been initialized yet? */
    bool               _isVcsInitialized;

    /** List of vdef files. */
    std::vector<Def*>    _vdefList;

    /** List of sdef files. */
    std::vector<Def*>    _sdefList;

    /** List of SystemC object files. */
    std::vector<Obj*>    _objList;

    /** Is there VHDL in the design. */
    bool _isVHDL;

    /** just the process-id in string form **/
    /** used for the top.<pid>.v file (systemc-on-top) **/
    std::string _pid;

    /** extra info for the top.v or sysc_skeleton.v file. */
    std::string             _extraInfo;

    /** error counter for invalid names, like 'foo[3]' */
    int errorcnt;
};

extern "C" void HDL_MODULE(const char *, const char *, const char *);

extern "C" void bf_exit(const char *);
extern "C" bool isElabMode();
extern "C" bool isImmediateElab();
int BF_find_parameter(const std::string &name, const std::string &val);
void snps_sysc_mark_process_as_internal(sc_process_handle);
void snps_sysc_mark_last_create_process_as_internal();

#endif // __VCS_DESIGN_H
