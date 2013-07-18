//
// File generated by /home/rui/work/root/bin/rootcint at Sun Feb 19 20:21:47 2012

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME TMhs3Dict
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "TMhs3Dict.h"

#include "TClass.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"

// START OF SHADOWS

namespace ROOT {
   namespace Shadow {
   } // of namespace Shadow
} // of namespace ROOT
// END OF SHADOWS

namespace ROOT {
   void TMhs3_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void *new_TMhs3(void *p = 0);
   static void *newArray_TMhs3(Long_t size, void *p);
   static void delete_TMhs3(void *p);
   static void deleteArray_TMhs3(void *p);
   static void destruct_TMhs3(void *p);
   static void streamer_TMhs3(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TMhs3*)
   {
      ::TMhs3 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TMhs3 >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TMhs3", ::TMhs3::Class_Version(), "./TMhs3.h", 9,
                  typeid(::TMhs3), DefineBehavior(ptr, ptr),
                  &::TMhs3::Dictionary, isa_proxy, 0,
                  sizeof(::TMhs3) );
      instance.SetNew(&new_TMhs3);
      instance.SetNewArray(&newArray_TMhs3);
      instance.SetDelete(&delete_TMhs3);
      instance.SetDeleteArray(&deleteArray_TMhs3);
      instance.SetDestructor(&destruct_TMhs3);
      instance.SetStreamerFunc(&streamer_TMhs3);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TMhs3*)
   {
      return GenerateInitInstanceLocal((::TMhs3*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TMhs3*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
TClass *TMhs3::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *TMhs3::Class_Name()
{
   return "TMhs3";
}

//______________________________________________________________________________
const char *TMhs3::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMhs3*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TMhs3::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TMhs3*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void TMhs3::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMhs3*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *TMhs3::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TMhs3*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
void TMhs3::Streamer(TBuffer &R__b)
{
   // Stream an object of class TMhs3.

   TThreadframe::Streamer(R__b);
}

//______________________________________________________________________________
void TMhs3::ShowMembers(TMemberInspector &R__insp)
{
      // Inspect the data members of an object of class TMhs3.
      TClass *R__cl = ::TMhs3::IsA();
      if (R__cl || R__insp.IsA()) { }
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*mC1", &mC1);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*mPad2", &mPad2);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*mPad1", &mPad1);
      R__insp.Inspect(R__cl, R__insp.GetParent(), "*mTotal0", &mTotal0);
      TThreadframe::ShowMembers(R__insp);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TMhs3(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMhs3 : new ::TMhs3;
   }
   static void *newArray_TMhs3(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::TMhs3[nElements] : new ::TMhs3[nElements];
   }
   // Wrapper around operator delete
   static void delete_TMhs3(void *p) {
      delete ((::TMhs3*)p);
   }
   static void deleteArray_TMhs3(void *p) {
      delete [] ((::TMhs3*)p);
   }
   static void destruct_TMhs3(void *p) {
      typedef ::TMhs3 current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TMhs3(TBuffer &buf, void *obj) {
      ((::TMhs3*)obj)->::TMhs3::Streamer(buf);
   }
} // end of namespace ROOT for class ::TMhs3

/********************************************************
* TMhs3Dict.cxx
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************/

#ifdef G__MEMTEST
#undef malloc
#undef free
#endif

#if defined(__GNUC__) && __GNUC__ >= 4 && ((__GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ >= 1) || (__GNUC_MINOR__ >= 3))
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

extern "C" void G__cpp_reset_tagtableTMhs3Dict();

extern "C" void G__set_cpp_environmentTMhs3Dict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("TMhs3.h");
  G__cpp_reset_tagtableTMhs3Dict();
}
#include <new>
extern "C" int G__cpp_dllrevTMhs3Dict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* TMhs3 */
static int G__TMhs3Dict_338_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   TMhs3* p = NULL;
   char* gvp = (char*) G__getgvp();
   int n = G__getaryconstruct();
   if (n) {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new TMhs3[n];
     } else {
       p = new((void*) gvp) TMhs3[n];
     }
   } else {
     if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
       p = new TMhs3;
     } else {
       p = new((void*) gvp) TMhs3;
     }
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__TMhs3DictLN_TMhs3));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMhs3Dict_338_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) TMhs3::Class());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMhs3Dict_338_0_10(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) TMhs3::Class_Name());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMhs3Dict_338_0_11(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 115, (long) TMhs3::Class_Version());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMhs3Dict_338_0_12(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      TMhs3::Dictionary();
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMhs3Dict_338_0_16(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((TMhs3*) G__getstructoffset())->StreamerNVirtual(*(TBuffer*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMhs3Dict_338_0_17(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) TMhs3::DeclFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMhs3Dict_338_0_18(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) TMhs3::ImplFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMhs3Dict_338_0_19(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 67, (long) TMhs3::ImplFileName());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__TMhs3Dict_338_0_20(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) TMhs3::DeclFileLine());
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__TMhs3Dict_338_0_21(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   TMhs3* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new TMhs3(*(TMhs3*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__TMhs3DictLN_TMhs3));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef TMhs3 G__TTMhs3;
static int G__TMhs3Dict_338_0_22(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   char* gvp = (char*) G__getgvp();
   long soff = G__getstructoffset();
   int n = G__getaryconstruct();
   //
   //has_a_delete: 0
   //has_own_delete1arg: 0
   //has_own_delete2arg: 0
   //
   if (!soff) {
     return(1);
   }
   if (n) {
     if (gvp == (char*)G__PVOID) {
       delete[] (TMhs3*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((TMhs3*) (soff+(sizeof(TMhs3)*i)))->~G__TTMhs3();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (TMhs3*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((TMhs3*) (soff))->~G__TTMhs3();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__TMhs3Dict_338_0_23(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   TMhs3* dest = (TMhs3*) G__getstructoffset();
   *dest = *(TMhs3*) libp->para[0].ref;
   const TMhs3& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* TMhs3 */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncTMhs3Dict {
 public:
  G__Sizep2memfuncTMhs3Dict(): p(&G__Sizep2memfuncTMhs3Dict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncTMhs3Dict::*p)();
};

size_t G__get_sizep2memfuncTMhs3Dict()
{
  G__Sizep2memfuncTMhs3Dict a;
  G__setsizep2memfunc((int)a.sizep2memfunc());
  return((size_t)a.sizep2memfunc());
}


/*********************************************************
* virtual base class offset calculation interface
*********************************************************/

   /* Setting up class inheritance */

/*********************************************************
* Inheritance information setup/
*********************************************************/
extern "C" void G__cpp_setup_inheritanceTMhs3Dict() {

   /* Setting up class inheritance */
   if(0==G__getnumbaseclass(G__get_linked_tagnum(&G__TMhs3DictLN_TMhs3))) {
     TMhs3 *G__Lderived;
     G__Lderived=(TMhs3*)0x1000;
     {
       TThreadframe *G__Lpbase=(TThreadframe*)G__Lderived;
       G__inheritance_setup(G__get_linked_tagnum(&G__TMhs3DictLN_TMhs3),G__get_linked_tagnum(&G__TMhs3DictLN_TThreadframe),(long)G__Lpbase-(long)G__Lderived,1,1);
     }
   }
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableTMhs3Dict() {

   /* Setting up typedef entry */
   G__search_typename2("Version_t",115,-1,0,-1);
   G__setnewtype(-1,"Class version identifier (short)",0);
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__TMhs3DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__TMhs3DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__TMhs3DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__TMhs3DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__TMhs3DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__TMhs3DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__TMhs3DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__TMhs3DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__TMhs3DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__TMhs3DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<UInt_t>",117,G__get_linked_tagnum(&G__TMhs3DictLN_vectorlEunsignedsPintcOallocatorlEunsignedsPintgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TString>",117,G__get_linked_tagnum(&G__TMhs3DictLN_vectorlETStringcOallocatorlETStringgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__TMhs3DictLN_reverse_iteratorlEvectorlETStringcOallocatorlETStringgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__TMhs3DictLN_vectorlETStringcOallocatorlETStringgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__TMhs3DictLN_reverse_iteratorlEvectorlETStringcOallocatorlETStringgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__TMhs3DictLN_vectorlETStringcOallocatorlETStringgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<std::bidirectional_iterator_tag,TObject*,std::ptrdiff_t,const TObject**,const TObject*&>",117,G__get_linked_tagnum(&G__TMhs3DictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*>",117,G__get_linked_tagnum(&G__TMhs3DictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,long>",117,G__get_linked_tagnum(&G__TMhs3DictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("iterator<bidirectional_iterator_tag,TObject*,long,const TObject**>",117,G__get_linked_tagnum(&G__TMhs3DictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Float_t>",117,G__get_linked_tagnum(&G__TMhs3DictLN_TVectorTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Double_t>",117,G__get_linked_tagnum(&G__TMhs3DictLN_TVectorTlEdoublegR),0,-1);
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* TMhs3 */
static void G__setup_memvarTMhs3(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__TMhs3DictLN_TMhs3));
   { TMhs3 *p; p=(TMhs3*)0x1000; if (p) { }
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__TMhs3DictLN_TCanvas),-1,-1,4,"mC1=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__TMhs3DictLN_TPad),-1,-1,4,"mPad2=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__TMhs3DictLN_TPad),-1,-1,4,"mPad1=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__TMhs3DictLN_TH1F),-1,-1,4,"mTotal0=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__TMhs3DictLN_TClass),-1,-2,4,"fgIsA=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarTMhs3Dict() {
}
/***********************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
***********************************************************/

/*********************************************************
* Member function information setup for each class
*********************************************************/
static void G__setup_memfuncTMhs3(void) {
   /* TMhs3 */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__TMhs3DictLN_TMhs3));
   G__memfunc_setup("CreateGraphics",1413,(G__InterfaceMethod) NULL, 105, -1, G__defined_typename("Int_t"), 0, 0, 1, 4, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeleteGraphics",1412,(G__InterfaceMethod) NULL, 105, -1, G__defined_typename("Int_t"), 0, 0, 1, 4, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("TMhs3",431,G__TMhs3Dict_338_0_3, 105, G__get_linked_tagnum(&G__TMhs3DictLN_TMhs3), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("Func0",444,(G__InterfaceMethod) NULL,121, -1, -1, 0, 0, 1, 1, 0, "", "functions running within thread", (void*) NULL, 1);
   G__memfunc_setup("Func1",445,(G__InterfaceMethod) NULL,121, -1, -1, 0, 0, 1, 1, 0, "", "dito; 	", (void*) NULL, 1);
   G__memfunc_setup("Func2",446,(G__InterfaceMethod) NULL,121, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Threadstart",1158,(G__InterfaceMethod) NULL,105, -1, G__defined_typename("Int_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Threadstop",1054,(G__InterfaceMethod) NULL,105, -1, G__defined_typename("Int_t"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Class",502,G__TMhs3Dict_338_0_9, 85, G__get_linked_tagnum(&G__TMhs3DictLN_TClass), -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (TClass* (*)())(&TMhs3::Class) ), 0);
   G__memfunc_setup("Class_Name",982,G__TMhs3Dict_338_0_10, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&TMhs3::Class_Name) ), 0);
   G__memfunc_setup("Class_Version",1339,G__TMhs3Dict_338_0_11, 115, -1, G__defined_typename("Version_t"), 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (Version_t (*)())(&TMhs3::Class_Version) ), 0);
   G__memfunc_setup("Dictionary",1046,G__TMhs3Dict_338_0_12, 121, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (void (*)())(&TMhs3::Dictionary) ), 0);
   G__memfunc_setup("IsA",253,(G__InterfaceMethod) NULL,85, G__get_linked_tagnum(&G__TMhs3DictLN_TClass), -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("ShowMembers",1132,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TMemberInspector' - 1 - insp", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("Streamer",835,(G__InterfaceMethod) NULL,121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 1);
   G__memfunc_setup("StreamerNVirtual",1656,G__TMhs3Dict_338_0_16, 121, -1, -1, 0, 1, 1, 1, 0, "u 'TBuffer' - 1 - b", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("DeclFileName",1145,G__TMhs3Dict_338_0_17, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&TMhs3::DeclFileName) ), 0);
   G__memfunc_setup("ImplFileLine",1178,G__TMhs3Dict_338_0_18, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&TMhs3::ImplFileLine) ), 0);
   G__memfunc_setup("ImplFileName",1171,G__TMhs3Dict_338_0_19, 67, -1, -1, 0, 0, 3, 1, 1, "", (char*)NULL, (void*) G__func2void( (const char* (*)())(&TMhs3::ImplFileName) ), 0);
   G__memfunc_setup("DeclFileLine",1152,G__TMhs3Dict_338_0_20, 105, -1, -1, 0, 0, 3, 1, 0, "", (char*)NULL, (void*) G__func2void( (int (*)())(&TMhs3::DeclFileLine) ), 0);
   // automatic copy constructor
   G__memfunc_setup("TMhs3", 431, G__TMhs3Dict_338_0_21, (int) ('i'), G__get_linked_tagnum(&G__TMhs3DictLN_TMhs3), -1, 0, 1, 1, 1, 0, "u 'TMhs3' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~TMhs3", 557, G__TMhs3Dict_338_0_22, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 1);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__TMhs3Dict_338_0_23, (int) ('u'), G__get_linked_tagnum(&G__TMhs3DictLN_TMhs3), -1, 1, 1, 1, 1, 0, "u 'TMhs3' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncTMhs3Dict() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
static void G__cpp_setup_global0() {

   /* Setting up global variables */
   G__resetplocal();

}

static void G__cpp_setup_global1() {
}

static void G__cpp_setup_global2() {
}

static void G__cpp_setup_global3() {
}

static void G__cpp_setup_global4() {
}

static void G__cpp_setup_global5() {
}

static void G__cpp_setup_global6() {

   G__resetglobalenv();
}
extern "C" void G__cpp_setup_globalTMhs3Dict() {
  G__cpp_setup_global0();
  G__cpp_setup_global1();
  G__cpp_setup_global2();
  G__cpp_setup_global3();
  G__cpp_setup_global4();
  G__cpp_setup_global5();
  G__cpp_setup_global6();
}

/*********************************************************
* Global function information setup for each class
*********************************************************/
static void G__cpp_setup_func0() {
   G__lastifuncposition();

}

static void G__cpp_setup_func1() {
}

static void G__cpp_setup_func2() {
}

static void G__cpp_setup_func3() {
}

static void G__cpp_setup_func4() {
}

static void G__cpp_setup_func5() {
}

static void G__cpp_setup_func6() {
}

static void G__cpp_setup_func7() {
}

static void G__cpp_setup_func8() {
}

static void G__cpp_setup_func9() {
}

static void G__cpp_setup_func10() {
}

static void G__cpp_setup_func11() {
}

static void G__cpp_setup_func12() {
}

static void G__cpp_setup_func13() {
}

static void G__cpp_setup_func14() {

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcTMhs3Dict() {
  G__cpp_setup_func0();
  G__cpp_setup_func1();
  G__cpp_setup_func2();
  G__cpp_setup_func3();
  G__cpp_setup_func4();
  G__cpp_setup_func5();
  G__cpp_setup_func6();
  G__cpp_setup_func7();
  G__cpp_setup_func8();
  G__cpp_setup_func9();
  G__cpp_setup_func10();
  G__cpp_setup_func11();
  G__cpp_setup_func12();
  G__cpp_setup_func13();
  G__cpp_setup_func14();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__TMhs3DictLN_TClass = { "TClass" , 99 , -1 };
G__linked_taginfo G__TMhs3DictLN_TBuffer = { "TBuffer" , 99 , -1 };
G__linked_taginfo G__TMhs3DictLN_TMemberInspector = { "TMemberInspector" , 99 , -1 };
G__linked_taginfo G__TMhs3DictLN_vectorlEunsignedsPintcOallocatorlEunsignedsPintgRsPgR = { "vector<unsigned int,allocator<unsigned int> >" , 99 , -1 };
G__linked_taginfo G__TMhs3DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__TMhs3DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__TMhs3DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__TMhs3DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__TMhs3DictLN_vectorlETStringcOallocatorlETStringgRsPgR = { "vector<TString,allocator<TString> >" , 99 , -1 };
G__linked_taginfo G__TMhs3DictLN_reverse_iteratorlEvectorlETStringcOallocatorlETStringgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TString,allocator<TString> >::iterator>" , 99 , -1 };
G__linked_taginfo G__TMhs3DictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR = { "iterator<bidirectional_iterator_tag,TObject*,long,const TObject**,const TObject*&>" , 115 , -1 };
G__linked_taginfo G__TMhs3DictLN_TCanvas = { "TCanvas" , 99 , -1 };
G__linked_taginfo G__TMhs3DictLN_TThreadframe = { "TThreadframe" , 99 , -1 };
G__linked_taginfo G__TMhs3DictLN_TVectorTlEfloatgR = { "TVectorT<float>" , 99 , -1 };
G__linked_taginfo G__TMhs3DictLN_TVectorTlEdoublegR = { "TVectorT<double>" , 99 , -1 };
G__linked_taginfo G__TMhs3DictLN_TH1F = { "TH1F" , 99 , -1 };
G__linked_taginfo G__TMhs3DictLN_TPad = { "TPad" , 99 , -1 };
G__linked_taginfo G__TMhs3DictLN_TMhs3 = { "TMhs3" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableTMhs3Dict() {
  G__TMhs3DictLN_TClass.tagnum = -1 ;
  G__TMhs3DictLN_TBuffer.tagnum = -1 ;
  G__TMhs3DictLN_TMemberInspector.tagnum = -1 ;
  G__TMhs3DictLN_vectorlEunsignedsPintcOallocatorlEunsignedsPintgRsPgR.tagnum = -1 ;
  G__TMhs3DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__TMhs3DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__TMhs3DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__TMhs3DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__TMhs3DictLN_vectorlETStringcOallocatorlETStringgRsPgR.tagnum = -1 ;
  G__TMhs3DictLN_reverse_iteratorlEvectorlETStringcOallocatorlETStringgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__TMhs3DictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR.tagnum = -1 ;
  G__TMhs3DictLN_TCanvas.tagnum = -1 ;
  G__TMhs3DictLN_TThreadframe.tagnum = -1 ;
  G__TMhs3DictLN_TVectorTlEfloatgR.tagnum = -1 ;
  G__TMhs3DictLN_TVectorTlEdoublegR.tagnum = -1 ;
  G__TMhs3DictLN_TH1F.tagnum = -1 ;
  G__TMhs3DictLN_TPad.tagnum = -1 ;
  G__TMhs3DictLN_TMhs3.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableTMhs3Dict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__TMhs3DictLN_TClass);
   G__get_linked_tagnum_fwd(&G__TMhs3DictLN_TBuffer);
   G__get_linked_tagnum_fwd(&G__TMhs3DictLN_TMemberInspector);
   G__get_linked_tagnum_fwd(&G__TMhs3DictLN_vectorlEunsignedsPintcOallocatorlEunsignedsPintgRsPgR);
   G__get_linked_tagnum_fwd(&G__TMhs3DictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__TMhs3DictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__TMhs3DictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__TMhs3DictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__TMhs3DictLN_vectorlETStringcOallocatorlETStringgRsPgR);
   G__get_linked_tagnum_fwd(&G__TMhs3DictLN_reverse_iteratorlEvectorlETStringcOallocatorlETStringgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__TMhs3DictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR);
   G__get_linked_tagnum_fwd(&G__TMhs3DictLN_TCanvas);
   G__get_linked_tagnum_fwd(&G__TMhs3DictLN_TThreadframe);
   G__get_linked_tagnum_fwd(&G__TMhs3DictLN_TVectorTlEfloatgR);
   G__get_linked_tagnum_fwd(&G__TMhs3DictLN_TVectorTlEdoublegR);
   G__get_linked_tagnum_fwd(&G__TMhs3DictLN_TH1F);
   G__get_linked_tagnum_fwd(&G__TMhs3DictLN_TPad);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__TMhs3DictLN_TMhs3),sizeof(TMhs3),-1,1280,(char*)NULL,G__setup_memvarTMhs3,G__setup_memfuncTMhs3);
}
extern "C" void G__cpp_setupTMhs3Dict(void) {
  G__check_setup_version(30051515,"G__cpp_setupTMhs3Dict()");
  G__set_cpp_environmentTMhs3Dict();
  G__cpp_setup_tagtableTMhs3Dict();

  G__cpp_setup_inheritanceTMhs3Dict();

  G__cpp_setup_typetableTMhs3Dict();

  G__cpp_setup_memvarTMhs3Dict();

  G__cpp_setup_memfuncTMhs3Dict();
  G__cpp_setup_globalTMhs3Dict();
  G__cpp_setup_funcTMhs3Dict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncTMhs3Dict();
  return;
}
class G__cpp_setup_initTMhs3Dict {
  public:
    G__cpp_setup_initTMhs3Dict() { G__add_setup_func("TMhs3Dict",(G__incsetup)(&G__cpp_setupTMhs3Dict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initTMhs3Dict() { G__remove_setup_func("TMhs3Dict"); }
};
G__cpp_setup_initTMhs3Dict G__cpp_setup_initializerTMhs3Dict;
