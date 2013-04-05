#!/usr/bin/python

# ***** BEGIN LICENSE BLOCK *****
# Version: MPL 1.1/GPL 2.0/LGPL 2.1
#
# The contents of this file are subject to the Mozilla Public License Version
# 1.1 (the "License"); you may not use this file except in compliance with
# the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS" basis,
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
# for the specific language governing rights and limitations under the
# License.
#
# The Original Code is Spicebird code.
#
# The Initial Developer of the Original Code is
#   Synovel Software Technologies
# Portions created by the Initial Developer are Copyright (C) 2009
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   Prasad Sunkari <prasad@synovel.com> (Original Author)
#
# Alternatively, the contents of this file may be used under the terms of
# either the GNU General Public License Version 2 or later (the "GPL"), or
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
# in which case the provisions of the GPL or the LGPL are applicable instead
# of those above. If you wish to allow use of your version of this file only
# under the terms of either the GPL or the LGPL, and not to allow others to
# use your version of this file under the terms of the MPL, indicate your
# decision by deleting the provisions above and replace them with the notice
# and other provisions required by the GPL or the LGPL. If you do not delete
# the provisions above, a recipient may use your version of this file under
# the terms of any one of the MPL, the GPL or the LGPL.
#
# ***** END LICENSE BLOCK *****

from __future__ import with_statement

################################## BEGIN CONFIG ##############################

# Paths
IDL_PATH        = '../generated/public/'
CPP_PATH        = '../generated/src/'

# Prefix to interface and class names
PREFIX_IDL      = 'csITp'
PREFIX_IMPL     = 'csTp'

# Timeout for D-Bus calls
DBUS_TIMEOUT    = -1

# License header for all output files
LICENCE_FILE    = 'license.txt'

################################### END CONFIG ###############################


import re
import sys, os, re
import lxml.etree as etree
import cPickle as pickle

from dbus import Signature
from uuid import uuid4 as uuid


# Telepathy Namespace
TP_NS = "http://telepathy.freedesktop.org/wiki/DbusSpec#extensions-v0"

# Cache of UUIDs
UUID_CACHE = None

# List of files to be compiled
XPIDL_SOURCES = []
CPP_SOURCES = []


# The GLib part is entirely taken from libglibcodegen.py that is
# distributed with the telepathy-glib code.
# XXX: We have to release this code under LGPL - not tri-license
def TypeInfo(s):
    #
    # Simple types.
    # We have direct mappings on Mozilla platform
    #
    if s == "y":
        return (('PRUint8 ', 'PRUint8 ', False, False, (), ()),
                ("guchar ", "G_TYPE_UCHAR", "UCHAR", False))

    elif s == "b":
        return (('PRBool ', 'PRBool ', False, False, (), ()),
                ("gboolean ", "G_TYPE_BOOLEAN", "BOOLEAN", False))

    elif s == "n":
        return (('PRInt16 ', 'PRInt16 ', False, False, (), ()),
                ("gint ", "G_TYPE_INT", "INT", False, False))

    elif s == "q":
        return (('PRUint16 ', 'PRUint16 ', False, False, (), ()),
                ("guint ", "G_TYPE_UINT", "UINT", False))

    elif s == "i":
        return (('PRInt32 ', 'PRInt32 ', False, False, (), ()),
                ("gint ", "G_TYPE_INT", "INT", False))

    elif s == "u":
        return (('PRUint32 ', 'PRUint32 ', False, False, (), ()),
                ("guint ", "G_TYPE_UINT", "UINT", False))

    elif s == "x":
        return (('PRInt64 ', 'PRInt64 ', False, False, (), ()),
                ("gint64 ", "G_TYPE_INT64", "INT64", False))

    elif s == "t":
        return (('PRUint64 ', 'PRUint64 ', False, False, (), ()),
                ("guint64 ", "G_TYPE_UINT64", "UINT64", False))

    elif s == "d":
        return (('PRFloat64 ', 'double ', False, False, (), ()),
                ("gdouble ", "G_TYPE_DOUBLE", "DOUBLE", False))

    elif s == "s":
        return (('nsCString ', 'AUTF8String ', False, False, (), ('nsStringGlue.h',)),
                ("gchar *", "G_TYPE_STRING", "STRING", True))

    elif s == "g":
        return (('nsCString ', 'ACString ', False, False, (), ('nsStringGlue.h',)),
                ("gchar *", "DBUS_TYPE_G_SIGNATURE", "STRING", True))

    elif s == "o":
        return (('nsCString ', 'ACString ', False, False, (), ('nsStringGlue.h',)),
                ("gchar *", "DBUS_TYPE_G_OBJECT_PATH", "BOXED", True))

    elif s == "v":
        return (('nsIVariant ', 'nsIVariant ', False, True, ('nsIVariant.idl',), ('nsIVariant.h',)),
                ("GValue *", "G_TYPE_VALUE", "BOXED", True))
    #
    # For all other types, we use nsISupports as the mozilla type
    # 1) nsIArray for the arrays
    # 2) nsIArray again for maps (currently maps are array of key value pairs)
    # 
    # Note: Most key-value pairs and structures are already interfaces
    #
    elif s == 'as':  
        return (('char *', 'string ', True, False, (), ()),
                ("gchar **", "G_TYPE_STRV", "BOXED", True))

    elif s == 'ay': 
        return (('PRUint8 ', 'PRUint8 ', True, False, (), ()),
                ("GArray *", "dbus_g_type_get_collection (\"GArray\", G_TYPE_UCHAR)", "BOXED", True))

    elif s == 'au': 
        return (('PRUint32 ', 'PRUint32 ', True, False, (), ()),
                ("GArray *", "DBUS_TYPE_G_UINT_ARRAY", "BOXED", True))

    elif s == 'ai': 
        return (('PRInt32 ', 'PRInt32 ', True, False, (), ()),
                ("GArray *", "DBUS_TYPE_G_INT_ARRAY", "BOXED", True))

    elif s == 'ax': 
        return (('PRInt64 ', 'PRInt64 ', True, False, (), ()),
                ("GArray *", "DBUS_TYPE_G_INT64_ARRAY", "BOXED", True))

    elif s == 'at': 
        return (('PRUint64 ', 'PRUint64 ', True, False, (), ()),
                ("GArray *", "DBUS_TYPE_G_UINT64_ARRAY", "BOXED", True))

    elif s == 'ad': 
        return (('PRFloat64 ', 'double ', True, False, (), ()),
                ("GArray *", "DBUS_TYPE_G_DOUBLE_ARRAY", "BOXED", True))

    elif s == 'ab': 
        return (('PRBool ', 'PRBool ', True, False, (), ()),
                ("GArray *", "DBUS_TYPE_G_BOOLEAN_ARRAY", "BOXED", True))

    elif s == 'ao': 
        return (('char **', 'string ', True, False, (), ()),
                ("GPtrArray *",
                 'dbus_g_type_get_collection ("GPtrArray",'
                 ' DBUS_TYPE_G_OBJECT_PATH)',
                 "BOXED", True))

    elif s == 'a{ss}': 
        return (('nsIArray ', 'nsIArray ', False, True, ('nsIArray.idl',), ('nsIArray.h',)),
                ("GHashTable *", "DBUS_TYPE_G_STRING_STRING_HASHTABLE", "BOXED", False))

    elif s[:2] == 'a{':  
        if s[2] not in ('y', 'b', 'n', 'q', 'i', 'u', 's', 'o', 'g'):
            raise Exception, "Can't index a hashtable off non-basic type " + s
        first = TypeInfo(s[2])[1]
        second = TypeInfo(s[3:-1])[1]

        return (('nsIArray ', 'nsIArray ', False, True, ('nsIArray.idl',), ('nsIArray.h',)),
                ("GHashTable *", "(dbus_g_type_get_map (\"GHashTable\", " + first[1] + ", " + second[1] + "))", "BOXED", False))

    elif s[:2] in ('a(', 'aa'): 
        gtype = TypeInfo(s[1:])[1][1]
        return (('nsIArray ', 'nsIArray ', False, True, ('nsIArray.idl',), ('nsIArray.h',)),
                ("GPtrArray *", "(dbus_g_type_get_collection (\"GPtrArray\", "+gtype+"))", "BOXED", True))

    elif s[:1] == '(': 
        gtype = "(dbus_g_type_get_struct (\"GValueArray\", "
        for subsig in Signature(s[1:-1]):
            gtype = gtype + TypeInfo(subsig)[1][1] + ", "
        gtype = gtype + "G_TYPE_INVALID))"

        return (('nsISupports ', 'nsISupports ', False, True, (), ()),
                ("GValueArray *", gtype, "BOXED", True))

    # Raise an exception if we don't know the type
    raise Exception, "Don't know the type for " + s


# Additional includes for generated C++ files.
def cross_includes(name):
    includes = [];
    if name == 'csTpConnectionInterfaceLocation':
        includes.append('csTpConnectionInterfaceSimplePresence.h')
    elif name == 'csTpConnectionInterfaceContactCapabilities':
        includes.append('csTpConnectionInterfaceRequests.h')
    elif name == 'csTpChannelTypeFileTransfer':
        includes.append('csTpChannelTypeTubes.h')
    elif name == 'csTpChannelTypeStreamTube':
        includes.append('csTpChannelTypeTubes.h')
    elif name == 'csTpChannelDispatchOperation':
        includes.append('csTpConnectionInterfaceRequests.h')

    return includes;

def telepathy_includes(name):
    includes = []
    exp = re.compile("(.+)(Type|Interface)")
    result = exp.search(name)
    interface = name
    if result is not None:
        interface = result.group(1)

    exp = re.compile("([a-z\d])([A-Z])")
    interface = exp.sub(r"\1-\2", interface)

    includes.append("telepathy-glib/%s.h" % interface.lower())

    return includes


# Get the preserved UUID, if exists
# or generate a new one.
def get_uuid(name):
    try:
        return UUID_CACHE[name]
    except KeyError:
        UUID_CACHE[name] = str(uuid())
        return UUID_CACHE[name]


# Taken from http://www.peterbe.com/plog/uniqifiers-benchmark
def make_unique(seq):
    seen = set()
    return [x for x in seq if x not in seen and not seen.add(x)]


# Copy out variables in getters
def moz_getter_copy(source, target, arg):
    if arg.dbus_type in ["o", "g", "s"]:
        return "%s.Assign(%s)" % (target, source)
    else:
        is_array = arg.mozinfo[2];
        is_interface = arg.mozinfo[3];
        counter = "*%sCount = %sCount; " % (target, source) if is_array else ""
        if not is_interface:
            return "%s*%s = %s" % (counter, target, source)
        elif not is_array:
            return "NS_IF_ADDREF(*%s = %s)" % (target, source)


# Copy values to object variables in setters
def moz_setter_copy(source, target, arg):
    if arg.dbus_type in ["o", "g", "s"]:
        return "%s.Assign(%s)" % (target, source)
    else:
        cpptype, idltype, is_array, is_interface, unused, unused = arg.mozinfo
        counter = "%sCount = %sCount; " % (target, source) if is_array else ""
        const_remove = "(%s*)" % cpptype if is_array else ""
        return "%s%s = %s%s" % (counter, target, const_remove, source)


# Dump code to convert glib datatypes to mozilla types
def convert_to_moz(src, dest, typ, tp_type):
    argstr = dest
    out = []

    # Integers of various lengths - nothing to be done here
    if typ in ("y", "b", "q", "i", "u", "x", "t", "d"):
        argstr = src
        
    # String types
    elif typ in ("s", "o", "g"):
        out.append("nsCString %s = nsDependentCString(%s);" % (dest, src))

    elif typ == "v":
        out.append("nsCOMPtr<nsIVariant> %s;" % dest)
        out.append("GValueToVariant(%s, getter_AddRefs(%s));" % (src, dest))

    # Arrays of directly assignable types (integers of various lengths)
    elif typ in ("ay", "ab", "aq", "ai", "au", "ax", "at", "ad"):
        gtype = TypeInfo(typ[1])[1][0].strip()
        moztype = TypeInfo(typ[1])[0][0].strip()
        out.append("PRUint32 %sCount = %s->len;" % (dest, src))
        out.append("%s *%s = (%s *)nsMemory::Alloc(sizeof(%s)*%sCount);" % (moztype, dest, moztype, moztype, dest));
        out.append("for (unsigned int i=0; i<%sCount; i++)" % dest)
        out.append("  %s[i] = g_array_index(%s, %s, i);" % (dest, src, gtype))
        argstr = "%sCount, %s" % (dest, dest)

    elif typ in ("as", "ao", "ag"):
        out.append("PRUint32 %sCount = 0;" % dest)
        out.append("for (char **pos = (char**)%s; *pos; pos++, %sCount++);" % (src, dest))
        out.append("char **%s = (char **)nsMemory::Alloc(%sCount * sizeof(char*));" % (dest, dest))
        out.append("for (PRUint32 i=0; i<%sCount; i++)" % dest)
        out.append("  %s[i] = (char *)nsMemory::Clone(%s[i], strlen(%s[i]) + 1);" % (dest, src, src))
        argstr = "%sCount, (const char **)%s" % (dest, dest)

    # It's a mapping
    elif typ.startswith("a{"):
        dest_interface = PREFIX_IDL + tp_type.replace("_", "")
        dest_class = PREFIX_IMPL + tp_type.replace("_", "")

        # We currently use an array of key-value pairs as a mapping
        out.append("nsCOMPtr<nsIArray> %s;" % dest)
        out.append("%s::Create((gpointer)%s, getter_AddRefs(%s));" % (dest_class, src, dest))

    # An array of non-basic type
    elif typ.startswith("a"):
        out.append("nsCOMPtr<nsIMutableArray> %s = do_CreateInstance(NS_ARRAY_CONTRACTID);" % dest)
        out.append("for (PRUint32 i=0; i<((GPtrArray*)%s)->len; i++) {" % src)
        out.append("  gpointer %s_item = g_ptr_array_index((GPtrArray*)%s, i);" % (src, src))
        tmpstr, tmpout = convert_to_moz("%s_item" % src, "%sItem" % dest, typ[1:], tp_type[:-2])
        for line in tmpout:
            out.append("  %s" % line)

        out.append("  %s->AppendElement(%sItem, PR_FALSE);" % (dest, dest))
        out.append("}")

    # A structure
    elif typ.startswith("("):
        dest_interface = PREFIX_IDL + tp_type.replace("_", "")
        dest_class = PREFIX_IMPL + tp_type.replace("_", "")

        out.append("nsCOMPtr<%s> %s;" % (dest_interface, dest))
        out.append("%s::Create((gpointer)%s, getter_AddRefs(%s));" % (dest_class, src, dest))

    return [argstr, out]


# Dump code to convert mozilla datatypes to glib types
def convert_to_glib(src, dest, typ, tp_type):
    argstr = dest
    out = []

    # Integers of various lengths - nothing to be done here
    if typ in ("y", "b", "q", "i", "u", "x", "t", "d"):
        argstr = src
        
    # String types
    elif typ in ("s", "o", "g"):
        out.append("char *%s = ToNewCString(%s);" % (dest, src))

    # Variable type
    elif typ == "v":
        out.append("GValue *%s = VariantToGValue(%s);" % (dest, src))

    # Arrays of directly assignable types (integers of various lengths)
    elif typ in ("ay", "ab", "aq", "ai", "au", "ax", "at", "ad"):
        gtype = TypeInfo(typ[1])[1][0]
        out.append("GArray *%s = g_array_new(false, false, sizeof(%s));" % (dest, gtype))
        out.append("for (PRUint32 i=0; i<%sCount; i++)" % src)
        out.append("  g_array_append_val(%s, %s[i]);" % (dest, src))
        
    elif typ in ("as", "ao", "ag"):
        out.append("char **%s = (char **)nsMemory::Alloc((%sCount + 1) * sizeof(char*));" % (dest, src))
        out.append("for (PRUint32 i=0; i<%sCount; i++)" % src)
        out.append("  %s[i] = (char *)nsMemory::Clone(%s[i], strlen(%s[i]) + 1);" % (dest, src, src))
        out.append("%s[%sCount] = NULL;" % (dest, src))
        argstr = "(const char**) %s" % argstr

    else:
        out.append("/* TODO */")
        argstr = "NULL"

    """
    # It's a mapping
    elif typ.startswith("a{"):
        dest_interface = PREFIX_IDL + tp_type.replace("_", "")
        dest_class = PREFIX_IMPL + tp_type.replace("_", "")

        out.append("nsCOMPtr<%s> %s;" % (dest_interface, dest))
        out.append("%s::Create(%s, getter_AddRefs(%s));" % (dest_class, src, dest))

    # An array of non-basic type
    elif typ.startswith("a"):
        out.append("nsCOMPtr<nsIMutableArray> %s = do_CreateInstance(NS_ARRAY_CONTRACTID)" % dest)
        out.append("for (PRUint32 i=0; i<%s->len; i++) {" % src)
        out.append("  gpointer %s_item = g_ptr_array_index(%s, i)" % (src, src))
        tmpstr, tmpout = convert_to_moz("%s_item" % src, "%sItem" % dest, typ[1:], tp_type[:-2])
        for line in tmpout:
            out.append("  %s" % line)

        out.append("  %s->AppendElement(%sItem, NS_FALSE);" % (dest, dest))
        out.append("}")

    # A structure
    elif typ.startswith("("):
        dest_interface = PREFIX_IDL + tp_type.replace("_", "")
        dest_class = PREFIX_IMPL + tp_type.replace("_", "")

        out.append("nsCOMPtr<%s> %s;" % (dest_interface, dest))
        out.append("nsresult rv;")
        out.append("")
        out.append("rv = %s::Create(%s, getter_AddRefs(%s));" % (dest_class, src, dest))
        out.append("if (NS_FAILED(rv))")
        out.append("  continue;")
    """

    return [argstr, out]


def get_gnames(args):
    return ", ".join([x.gname() for x in args])


def get_moznames(args):
    return ", ".join([x.mozname2() for x in args])


# XXX: make it clean
def get_cppstr(args, impl=None):
    return ", ".join([x.cppstr(impl) for x in args])


def get_idlstr(args):
    return ", ".join([x.idlstr() for x in args])


def get_gstr(args):
    return ", ".join([x.gstr() for x in args])


# Proxy names.
# We support a few interfaces, for others return None
def get_proxyname(name):
    exp = re.compile("^(Connection|Channel)")
    found = exp.search(name)
    if found is None:
        return None

    exp = re.compile("(.+)(Type|Interface)")
    result = exp.search(name)
    interface = name
    if result is not None:
        interface = result.group(1)

    return "Tp%s" % interface


# XXX
def get_baseclass(name):
    proxy = get_proxyname(name)
    return "_cs%sProxyBase" % proxy


_license = None
def license():
    global _license
    if _license is None:
        with open('license.txt', 'r') as f:
            _license = f.read()

    return _license


def docstring(element):
    docstr = element.find('{%s}docstring' % TP_NS)
    if docstr is not None:
        return docstr.text.strip()
    return None

def snakecase(string):
    exp = re.compile("([A-Z]+)([A-Z][a-z])")
    string = exp.sub(r"\1_\2", string)

    exp = re.compile("([a-z\d])([A-Z])")
    string = exp.sub(r"\1_\2", string)

    return string.replace("-", "_").lower()


class TpParam:
    def __init__(self, element, index, is_out = None):
        self.element = element
        self.is_out = is_out
        self._cppstr, self._cppoutstr, self._idlstr, self._gstr = (None, None, None, None)
        self._cppdecl, self._idldecl = (None, None)
        self._mozname, self._gname = (None, None)

        self.dbus_type = element.attrib['type']
        try:
            self.tp_type = element.attrib['{%s}type' % TP_NS]
        except KeyError:
            self.tp_type = None

        try:
            self.basename = element.attrib['name']
            if str(self.basename) == "Attribute":
                self.basename = "Name"
        except KeyError:
            if is_out is not None:
                self.basename = 'Out_%u' % index
            else:
                self.basename = 'In_%u' % index

        self.mozinfo, self.ginfo = TypeInfo(self.dbus_type)


    def docstring(self):
        return docstring(self.element)


    def cppstr(self, impl = None):
        if self._cppstr is None:
            cpptype, idltype, is_array, is_interface, unused, unused = self.mozinfo
            prefix = 'PRUint32 %sCount, ' % self.mozname() if is_array \
                     else 'const ' if self.dbus_type in ("s", "g", "o") else ""
            suffix = '*' if is_interface or is_array \
                     else '&' if self.dbus_type in ("s", "g", "o") else ""

            if self.dbus_type in ("as", "ag", "ao"):
                prefix = "%sconst " % prefix

            self._cppstr = "%s%s%s%s" % (prefix, cpptype, suffix, self.mozname())

        return self._cppstr.replace("nsCString", "nsACString") if impl else self._cppstr


    def cppoutstr(self, impl = None):
        if self._cppoutstr is None:
            cpptype, idltype, is_array, is_interface, unused, unused = self.mozinfo
            prefix = 'PRUint32 %sCount, ' % "*%s" % self.mozname() if is_array \
                     else 'const ' if self.dbus_type in ("s", "g", "o") else ""
            suffix = '*' if is_interface or is_array \
                     else '&' if self.dbus_type in ("s", "g", "o") else ""
            if self.is_out is not None:
                if self.dbus_type in ("s", "g", "o"):
                    prefix = ""
                else:
                    suffix = suffix + "*"

            self._cppoutstr = "%s%s%s%s" % (prefix, cpptype, suffix, self.mozname())

        return self._cppoutstr.replace("nsCString", "nsACString") if impl else self._cppoutstr


    def idlstr(self, direction="in"):
        if self._idlstr is None:
            cpptype, idltype, is_array, is_interface, unused, unused = self.mozinfo
            prefix = 'PRUint32 %sCount, [array, size_is(%sCount)] %s ' % (self.mozname(), self.mozname(), direction) if is_array else ''
            self._idlstr = "%s %s%s%s" % (direction, prefix, idltype, self.mozname())

        return self._idlstr


    # Used for structs and properties to create a member item
    # In case of structs arrays could be member items, in which case we also want to store the length.
    def cppdecl(self):
        if self._cppdecl is None:
            cpptype, idltype, is_array, is_interface, unused, unused = self.mozinfo
            if is_interface is True:
                self._cppdecl = "nsCOMPtr<%s> m_%s" % (cpptype.strip(), self.basename.replace("_", ""))
            else:
                cpptype = "%s*" % cpptype if is_array is True else cpptype
                name = self.basename.replace("_", "")
                counter = "PRUint32 m_%sCount; " % name if is_array is True else ""
                self._cppdecl = "%s%sm_%s" % (counter, cpptype, name);

        return self._cppdecl


    # Used for structs and properties to create an attribute in IDL
    def idldecl(self, readonly=True):
        if self._idldecl is None:
            cpptype, idltype, is_array, is_interface, unused, unused = self.mozinfo
            name = self.basename.replace("_", "")
            access = "readonly " if readonly else ""
            if is_array is not True:
                self._idldecl = "%sattribute %s%s" % (access, idltype, name.replace(name[0], name[0].lower(), 1))
            else:
                # We currently don't have arrays that need to be writter to.
                self._idldecl = "void get%s(%s)" % (name, self.idlstr("out"))

        return self._idldecl


    def gstr(self):
        if self._gstr is None:
            ctype, gtype, marshal, is_pointer = self.ginfo
            const = 'const ' if is_pointer else ''
            self._gstr = '%s%s%s' % (const, ctype, self.gname())

        return self._gstr


    def mozname(self):
        if self._mozname is None:
            self._mozname = 'a%s' % self.basename.replace("_", "")

        return self._mozname


    def mozname2(self):
        cpptype, idltype, is_array, is_interface, unused, unused = self.mozinfo
        prefix = '%sCount, ' % self.mozname() if is_array else ''
        return "%s%s" % (prefix, self.mozname())


    def gname(self):
        if self._gname is None:
            self._gname = '%s' % self.basename.lower()

        return self._gname


    def interface_includes(self):
        return self.mozinfo[4]


    def header_includes(self):
        return self.mozinfo[5]


    def to_moz(self, src=None, dest=None):
        if src is None:
            src = self.gname()
        if dest is None:
            dest = 'c%s' % self.basename.replace("_", "")

        return convert_to_moz(src, dest, self.dbus_type, self.tp_type)


    def to_glib(self, src=None, dest=None):
        if src is None:
            src = self.mozname()
        if dest is None:
            dest = 'c%s' % self.basename.replace("_", "")

        return convert_to_glib(src, dest, self.dbus_type, self.tp_type)


class TpMember:
    def __init__(self, interface, member):
        self.member = member
        self.interface = interface
 
        self.name = self.member.attrib["name"]
        
        self.sub_interfaces     = []
        self.interface_items    = []
        self.interface_includes = []
        self.interface_forwards = []
        
        self.private_items      = []
        self.protected_items    = []
        self.public_items       = []
        self.header_includes    = []
        self.header_forwards    = []
        
        self.implementation     = []

    def b(self, str):
        self.implementation.append(str)

    def s(self, str):
        self.sub_interfaces.append(str)

    def h(self, str):
        self.header_forwards.append(str)

structures = {}
class TpStruct(TpMember):
    def __call__(self, is_mapping=False):
        self.is_mapping = is_mapping
        my_interface = PREFIX_IDL + self.name.replace("_", "")
        my_class = PREFIX_IMPL + self.name.replace("_", "")

        # Comment
        docstr = docstring(self.member)
        if docstr is not None:
            self.s("/*")
            self.s(" * %s" % docstr)
            self.s(" */")

        # Interface header (uuid etc)
        self.s("[scriptable, uuid(%s)]" % str(get_uuid(my_interface)))
        self.s("interface %s : nsISupports" % my_interface)
        self.s("{")

        # C++ class declaration
        self.h("class %s: public %s" % (my_class, my_interface))
        self.h("{")
        self.h("public:")
        self.h("  NS_DECL_ISUPPORTS")
        self.h("  NS_DECL_%s" % my_interface.upper())
        self.h("")

        self.args = []
        for item in self.member.findall('{%s}member' % TP_NS):
            param = TpParam(item, len(self.args), True)
            self.args.append(param)
            self.interface_includes.extend(param.interface_includes())
            self.header_includes.extend(param.header_includes())

        # Interface members
        for arg in self.args:
            docstr = arg.docstring()
            if docstr is not None:
                self.s('  /* %s */' % docstr)
            self.s("  %s;" % arg.idldecl())

        if not self.is_mapping:
            self.s("\n  [noscript] gpointer toGLib();")
        
        # Interface footer
        self.s("};")
        self.s("")

        #
        # C++ Implementation
        #
        # Add attributes to the C++ declaration
        self.h("  %s(%s);" % (my_class, get_cppstr(self.args)))
        self.h("  static NS_METHOD Create(%s, void **aResult);" % get_cppstr(self.args))
        if self.is_mapping:
            self.h("  static NS_METHOD Create(gpointer aGLibItem, nsIArray **array);")
            self.h("  static NS_METHOD ToGLib(nsIArray *aObj, gpointer *_retval);")
        else:
            self.h("  static NS_METHOD Create(gpointer aGLibItem, void **aResult);")

        self.h("")
        self.h("private:")
        self.h("  ~%s();" % my_class)
        self.h("")
        self.h("protected:")
        for arg in self.args:
            self.h("  %s;" % arg.cppdecl())
 
        # End C++ class declaration
        self.h("};")
        self.h("")

        # Implementation of static "Create" function
        self.b("/*")
        self.b(" *  Implementation of %s" % my_class)
        self.b(" */")
        self.b("")
        self.b("NS_IMPL_ISUPPORTS1(%s, %s)" % (my_class, my_interface))
        self.b("")
        self.b("NS_METHOD")
        self.b("%s::Create(%s, void **aResult)" % (my_class, get_cppstr(self.args)))
        self.b("{")
        self.b("  %s *it = " % my_interface)
        self.b("          new %s(%s);" % (my_class, get_moznames(self.args)))
        self.b("  if (!it)")
        self.b("    return NS_ERROR_OUT_OF_MEMORY;")
        self.b("")
        self.b("  NS_ADDREF(it);")
        self.b("  nsresult rv = it->QueryInterface(NS_GET_IID(%s), aResult);" % my_interface)
        self.b("  NS_RELEASE(it);")
        self.b("")
        self.b("  return rv;")
        self.b("}")
        self.b("")

        self.dump_converters()

        # Constructor & Destructor
        self.b("%s::%s(%s)" % (my_class, my_class, get_cppstr(self.args)))
        self.b("{")
        for arg in self.args:
            name = arg.basename.replace("_", "")
            self.b("  %s;" % moz_setter_copy("a"+name, "m_"+name, arg))
        self.b("}")
        self.b("")
        self.b("%s::~%s()" % (my_class, my_class))
        self.b("{}")
        self.b("")

        # Implementation of getters
        for arg in self.args:
            name = arg.basename.replace("_", "")
            self.b("NS_IMETHODIMP")
            self.b("%s::Get%s(%s)" % (my_class, name, arg.cppoutstr(True)))
            self.b("{")
            self.b("  %s;" % moz_getter_copy("m_"+name, "a"+name, arg))
            self.b("  return NS_OK;")
            self.b("}")
            self.b("")

        structures[self.name] = self
        return self

    def dump_converters(self):
        glib_struct_type = "TP_%s_TYPE_%s" % ("HASH" if self.is_mapping else "STRUCT", self.name.upper())
        my_interface = PREFIX_IDL + self.name.replace("_", "")
        my_class = PREFIX_IMPL + self.name.replace("_", "")

        # Construct the class object from a glib item
       
        if self.is_mapping:
            self.b("NS_METHOD")
            self.b("%s::Create(gpointer aGLibItem, nsIArray **aResult)" % my_class)
            self.b("{")
            self.b("  nsCOMPtr<nsIMutableArray> array = do_CreateInstance(NS_ARRAY_CONTRACTID);")
            self.b("  GHashTable *hashTable = (GHashTable*)aGLibItem;")
            self.b("  GHashTableIter iter;")
            self.b("  gpointer keyPtr, valuePtr;")
            self.b("")
            self.b("  g_hash_table_iter_init(&iter, hashTable);")
            self.b("  while (g_hash_table_iter_next(&iter, &keyPtr, &valuePtr)) {")

            arg = self.args[0];
            if arg.dbus_type[0] == "n" or arg.dbus_type[0] == "i":
                self.b("    %s = GPOINTER_TO_GINT(keyPtr);" % arg.gstr())
            if arg.dbus_type[0] == "q" or arg.dbus_type[0] == "u":
                self.b("    %s = GPOINTER_TO_UINT(keyPtr);" % arg.gstr())
            else:
                self.b("    %s = (%s)keyPtr;" % (arg.gstr(), arg.ginfo[0]))

            arg = self.args[1];
            if arg.dbus_type[0] == "n" or arg.dbus_type[0] == "i":
                self.b("    %s = GPOINTER_TO_GINT(valuePtr);" % arg.gstr())
            if arg.dbus_type[0] == "q" or arg.dbus_type[0] == "u":
                self.b("    %s = GPOINTER_TO_UINT(valuePtr);" % arg.gstr())
            else:
                self.b("    %s = (%s)valuePtr;" % (arg.gstr(), arg.ginfo[0]))

            self.b("")
            converted_names = []
            for arg in self.args:
                argstr, converted = arg.to_moz()
                if len(converted) >= 1:
                    for line in converted:
                        self.b("    %s" % line)
         
                converted_names.append(argstr)
         
            self.b("")
            self.b("    %s *temp = new %s(%s);" % (my_interface, my_class, ", ".join(converted_names)))
            self.b("    if (!temp)")
            self.b("      return NS_ERROR_OUT_OF_MEMORY;")
            self.b("")
            self.b("    nsCOMPtr<%s> it = do_QueryInterface(temp);" % my_interface)
            self.b("    array->AppendElement(it, false);")
            self.b("  }")
            self.b("")
            self.b("  NS_ADDREF(*aResult = array);")
            self.b("  return NS_OK;")
        else:
            self.b("NS_METHOD")
            self.b("%s::Create(gpointer aGLibItem, void **aResult)" % my_class)
            self.b("{")
            for arg in self.args:
                self.b("  %s;" % arg.gstr())

            self.b("")
            self.b("  GValue structure = { 0 };")
            self.b("  g_value_init(&structure, %s);" % glib_struct_type)
            self.b("  g_value_set_static_boxed(&structure, aGLibItem);")
            self.b("")
            self.b("  if (!dbus_g_type_struct_get(&structure,")
            self.b("           %s," % ", ".join(["%s, &%s" % (i, self.args[i].gname()) for i in range(len(self.args))]))
            self.b("           G_MAXUINT))")
            self.b("    return NS_ERROR_FAILURE;")
            self.b("")

            converted_names = []
            for arg in self.args:
                argstr, converted = arg.to_moz()
                if len(converted) >= 1:
                    for line in converted:
                        self.b("  %s" % line)
         
                converted_names.append(argstr)
         
            self.b("  %s *it = new %s(%s);" % (my_interface, my_class, ", ".join(converted_names)))
            self.b("  if (!it)")
            self.b("    return NS_ERROR_OUT_OF_MEMORY;")
            self.b("")
            self.b("  NS_ADDREF(it);")
            self.b("  nsresult rv = it->QueryInterface(NS_GET_IID(%s), aResult);" % my_interface)
            self.b("  NS_RELEASE(it);")
            self.b("")
            self.b("  return rv;")

        self.b("}")
        self.b("")

        if self.is_mapping:
            self.b("NS_METHOD")
            self.b("%s::ToGLib(nsIArray *aObj, gpointer *_retval)" % my_class)
            self.b("{")
            self.b("  *_retval = NULL; /* TODO */")
            self.b("  return NS_OK;")
            self.b("}")
            self.b("")
        else:
            self.b("NS_IMETHODIMP")
            self.b("%s::ToGLib(gpointer *_retval)" % my_class)
            self.b("{")
            self.b("  *_retval = NULL; /* TODO */")
            self.b("  return NS_OK;")
            self.b("}")
            self.b("")


class TpSignal(TpMember):
    def __call__(self):
        self.args = []
        for item in self.member.findall('arg'):
            param = TpParam(item, len(self.args))
            self.args.append(param)
            self.interface_includes.extend(param.interface_includes())
            self.header_includes.extend(param.header_includes())

        self.generate()
        return self

    def generate(self):
        glib_function = 'tp_cli_%s_connect_to_%s' % (snakecase(self.interface.name), snakecase(self.name))
        callback_name = '%s%sObserver' % (self.interface.interface_name, self.name)

        # Signal Handler

        self.b("static void")
        self.b("%sSignalCallback(%s *proxy," % (self.name, get_proxyname(self.interface.name)))
        if len(self.args) > 0:
            self.b("    %s," % get_gstr(self.args))
        self.b("    gpointer user_data, GObject *weak_object)")
        self.b("{")
        self.b("  %s *obj = (%s *)user_data;" % (self.interface.class_name, self.interface.class_name))
        self.b("  if (!obj)")
        self.b("    return;")
        self.b("")
        self.b("  obj->Handle%s(%s);" % (self.name, get_gnames(self.args)))
        self.b("}\n\n")

        # Signal Handler

        self.b("void")
        self.b("%s::Handle%s(%s)" % (self.interface.class_name, self.name, get_gstr(self.args)))
        self.b("{")
        self.b("  if (!m_Proxy)")
        self.b("    return;")
        self.b("")
        self.b("  PRUint32 length;")
        self.b("  m_%sObservers->GetLength(&length);" % self.name)
        self.b("  nsCOMPtr<%s> observer;" % callback_name)
        self.b("")

        converted_names = []
        for arg in self.args:
            argstr, converted = arg.to_moz()
            if len(converted) >= 1:
                for line in converted:
                    self.b("  %s" % line)

            converted_names.append(argstr)

        self.b("")
        self.b("  for (PRUint32 i=0; i<length; i++) {")
        self.b("    observer = do_QueryElementAt(m_%sObservers, i);" % self.name)
        self.b("    observer->On%s(%s);" % (self.name, ", ".join(converted_names)))
        self.b("  }")
        self.b("}\n\n")

        # Connect to Signal
 
        self.b("NS_IMETHODIMP")
        self.b("%s::ConnectTo%s(%s *observer)" % (self.interface.class_name, self.name, callback_name))
        self.b("{")
        self.b("  if (!m_Proxy)")
        self.b("    return NS_ERROR_NOT_INITIALIZED;")
        self.b("")
        self.b("  NS_ENSURE_ARG_POINTER(observer);")
        self.b("")
        self.b("  if (!m_%sObservers) {" % self.name)
        self.b("    m_%sObservers = do_CreateInstance(NS_ARRAY_CONTRACTID);" % self.name)
        self.b("    %s(m_Proxy," % glib_function)
        self.b("        %sSignalCallback, this, NULL, NULL, NULL);" % self.name)
        self.b("  }")
        self.b("")
        self.b("  m_%sObservers->AppendElement(observer, PR_FALSE);" % self.name)
        self.b("  return NS_OK;")
        self.b("}\n\n")
 
        # Disconnect From Signal
 
        self.b("NS_IMETHODIMP")
        self.b("%s::DisconnectFrom%s(%s *observer)" % (self.interface.class_name, self.name, callback_name))
        self.b("{")
        self.b("  if (!m_%sObservers)" % self.name)
        self.b("    return NS_ERROR_NOT_INITIALIZED;")
        self.b("")
        self.b("  PRUint32 idx;")
        self.b("  nsresult rv = m_%sObservers->IndexOf(0, observer, &idx);" % self.name)
        self.b("  if(NS_FAILED(rv))")
        self.b("    return rv;")
        self.b("")
        self.b("  return m_%sObservers->RemoveElementAt(idx);" % self.name)
        self.b("}\n\n")

        # Declarations, Interfaces, Includes ...
 
        self.interface_items.append("  void connectTo%s(in %s observer);" % (self.name, callback_name))
        self.interface_items.append("  void disconnectFrom%s(in %s observer);" % (self.name, callback_name))
        self.interface_items.append("")
 
        self.public_items.append("  void Handle%s(%s);" % (self.name, get_gstr(self.args)))
        self.protected_items.append("  nsCOMPtr<nsIMutableArray> m_%sObservers;" % self.name)

        # Dump sub-interface for the callback!

        self.s("[scriptable, uuid(%s)]" % str(get_uuid(callback_name)))
        self.s("interface %s : nsISupports" % callback_name)
        self.s("{")
        self.s("  void on%s(%s);" % (self.name, get_idlstr(self.args)))
        self.s("};")
        self.s("")


class TpMethod(TpMember):
    def __call__(self):
        self.inargs  = []
        self.outargs = []
        for item in self.member.findall('arg'):
            direction = item.attrib['direction']
            param = None
            if direction == 'in':
                param = TpParam(item, len(self.inargs))
                self.inargs.append(param)
            else:
                param = TpParam(item, len(self.outargs), True)
                self.outargs.append(param)

            self.interface_includes.extend(param.interface_includes())
            self.header_includes.extend(param.header_includes())

        self.generate()
        return self

    def generate(self):
        glib_function = 'tp_cli_%s_call_%s' % (snakecase(self.interface.name), snakecase(self.name))
        callback_name = '%s%s%sCB' % (PREFIX_IDL, self.interface.name, self.name)
    
        # Callback function
 
        self.b("static void")
        self.b("%sResponse(%s *proxy," % (self.name, get_proxyname(self.interface.name)))
        if len(self.outargs) > 0:
            self.b("    %s," % get_gstr(self.outargs))
        self.b("    const GError *error, gpointer user_data, GObject *weak_object)")
        self.b("{")
        self.b("  %s *callback = (%s *)user_data;" % (callback_name, callback_name))
        self.b("  if (!callback)")
        self.b("    return;")
        self.b("")
        self.b("  if (error != NULL) {")
        self.header_includes.append("nsStringGlue.h")
        self.b("    callback->On%sError(nsDependentCString(g_quark_to_string(error->domain))," % self.name)
        self.b("                        error->code, nsDependentCString(error->message));")
        self.b("    return;")
        self.b("  }")
        self.b("")
        
        converted_names = []
        for arg in self.outargs:
            argstr, converted = arg.to_moz()
            if len(converted) >= 1:
                for line in converted:
                    self.b("  %s" % line)

            converted_names.append(argstr)

        self.b("")
        self.b("  callback->On%sDone(%s);" % (self.name, ", ".join(converted_names)))
        self.b("  NS_IF_RELEASE(callback);")
        self.b("}\n\n")

        # Implementation
 
        self.b("NS_IMETHODIMP")
        if len(self.inargs) > 0:
            self.b("%s::Call%s(%s," % (self.interface.class_name, self.name, get_cppstr(self.inargs, True)))
            self.b("    %s *cb)" % callback_name)
        else:
            self.b("%s::Call%s(%s *cb)" % (self.interface.class_name, self.name, callback_name))
        self.b("{")
        self.b("  if (!m_Proxy)")
        self.b("    return NS_ERROR_NOT_INITIALIZED;")
        self.b("")
        
        converted_names = []
        for arg in self.inargs:
            argstr, converted = arg.to_glib()
            if len(converted) >= 1:
                for line in converted:
                    self.b("  %s" % line)

            converted_names.append(argstr)

        self.b("")
        self.b("  NS_IF_ADDREF(cb);")
        self.b("  %s(m_Proxy, %d," % (glib_function, DBUS_TIMEOUT))
        if len(self.inargs) > 0:
          self.b("      %s," % ", ".join(converted_names))
        self.b("      cb? %sResponse: NULL, cb? cb: NULL, NULL, NULL);" % self.name)
        self.b("")
        self.b("  return NS_OK;")
        self.b("}\n\n")
 
        # Declaration, Interfaces, Includes ...
 
        comma = ', ' if (len(self.inargs) > 0) else ''
        self.interface_items.append("  void call%s(%s%sin %s cb);" % (self.name, get_idlstr(self.inargs), comma, callback_name))
        self.interface_items.append("")

        # Dump sub-interface for the callback!

        self.s("[scriptable, uuid(%s)]" % str(get_uuid(callback_name)))
        self.s("interface %s : nsISupports" % callback_name)
        self.s("{")
        self.s("  void on%sError(in ACString aErrorDomain, in PRUint32 aErrorCode, in AUTF8String aErrorDesc);" % self.name)
        self.s("  void on%sDone(%s);" % (self.name, get_idlstr(self.outargs)))
        self.s("};")
        self.s("")


class TpProperty(TpMember):
    def __call__(self):
        docstr = docstring(self.member)
        if docstr is not None and len(docstr) > 0:
            self.interface_items.append('  /* %s */' % docstr)

        self.param = TpParam(self.member, 0, True);
        self.interface_includes.extend(self.param.interface_includes())
        self.header_includes.extend(self.param.header_includes())

        self.readonly = True if (self.member.attrib['access'] == 'read') else ''

        self.generate()
        return self

    # TODO: Writing properties
    #       Converting types from GValue
    def generate(self):
        callback_name = '%s%s%sCB' % (PREFIX_IDL, self.interface.name, self.name)
    
        # Callback function
 
        self.b("static void")
        self.b("%sResponse(TpProxy *proxy, const GValue *out," % self.name)
        self.b("    const GError *error, gpointer user_data, GObject *weak_object)")
        self.b("{")
        self.b("  %s *callback = (%s *)user_data;" % (callback_name, callback_name))
        self.b("  if (!callback)")
        self.b("    return;")
        self.b("")
        self.b("  if (error != NULL) {")
        self.header_includes.append("nsStringGlue.h")
        self.b("    callback->GetProperty%sError(nsDependentCString(g_quark_to_string(error->domain))," % self.name)
        self.b("                                 error->code, nsDependentCString(error->message));")
        self.b("    return;")
        self.b("  }")
        self.b("")

        self.b("  %s %s;" % (self.param.ginfo[0], self.param.gname()))
        if self.param.ginfo[2] == 'BOXED':
            self.b("  %s = (%s)g_value_get_boxed(out);" % (self.param.gname(), self.param.ginfo[0]))

        argstr, converted = self.param.to_moz()
        if len(converted) >= 1:
            for line in converted:
                self.b("  %s" % line)

        self.b("")
        self.b("  callback->GetProperty%sDone(%s);" % (self.name, argstr))
        self.b("  NS_IF_RELEASE(callback);")
        self.b("}\n\n")

        # Implementation
 
        self.b("NS_IMETHODIMP")
        self.b("%s::GetProperty%s(%s *cb)" % (self.interface.class_name, self.name, callback_name))
        self.b("{")
        self.b("  if (!m_Proxy)")
        self.b("    return NS_ERROR_NOT_INITIALIZED;")
        self.b("")
        self.b("  NS_IF_ADDREF(cb);")
        self.b("  tp_cli_dbus_properties_call_get(m_Proxy, %d," % DBUS_TIMEOUT)
        self.b("      \"%s\"," % self.interface.root.attrib["name"])
        self.b("      \"%s\"," % self.name)
        self.b("      cb? %sResponse: NULL, cb? cb: NULL, NULL, NULL);" % self.name)
        self.b("")
        self.b("  return NS_OK;")
        self.b("}\n\n")
 
        # Declaration, Interfaces, Includes ...
 
        self.interface_items.append("  void getProperty%s(in %s cb);" % (self.name, callback_name))
        self.interface_items.append("")

        # Dump sub-interface for the callback!

        self.s("[scriptable, uuid(%s)]" % str(get_uuid(callback_name)))
        self.s("interface %s : nsISupports" % callback_name)
        self.s("{")
        self.s("  void getProperty%sError(in ACString aErrorDomain, in PRUint32 aErrorCode, in ACString aErrorDesc);" % self.name)
        self.s("  void getProperty%sDone(%s);" % (self.name, self.param.idlstr()))
        self.s("};")
        self.s("")


class TpEnumeration(TpMember):
    def __call__(self):
        docstr = docstring(self.member)
        if docstr is not None:
            self.interface_items.append('  /* %s */' % docstr)

        for item in self.member.findall('{%s}enumvalue' % TP_NS):
            suffix = item.attrib['suffix']
            value = item.attrib['value']
            self.interface_items\
                .append('  const short %s_%s = %s;' % (self.name, suffix, value))

        self.interface_items.append("")
        return self


class TpFlags(TpMember):
    def __call__(self):
        docstr = docstring(self.member)
        if docstr is not None:
            self.interface_items.append('  /* %s */' % docstr)

        for item in self.member.findall('{%s}flag' % TP_NS):
            suffix = item.attrib['suffix']
            value = item.attrib['value']
            self.interface_items\
                .append('  const short %s_%s = %s;' % (self.name, suffix, value))

        self.interface_items.append("")
        return self



# Interface code generation flags
NO_IDL          = 0x0
NO_SOURCE       = 0x2
NO_DEFAULT      = 0x4

class TpInterface:
    
    def __init__(self, name, node, flags):
        self.name = name
        self.flags = flags
        self.interface_name = PREFIX_IDL + name
        self.class_name = PREFIX_IMPL + name
        self.proxy_name = get_proxyname(self.name)
        self.root = node
        self.members = []
        
    def __call__(self):
        if not get_proxyname(self.name) and not self.flags & NO_DEFAULT:
            return

        for element in self.root.iterchildren():
            if (element.tag == 'signal'):
                self.members.append(TpSignal(self, element)())
            elif (element.tag == 'method'):
                self.members.append(TpMethod(self, element)())
            elif (element.tag == 'property'):
                self.members.append(TpProperty(self, element)())
            elif (element.tag == '{%s}mapping' % TP_NS):
                self.members.append(TpStruct(self, element)(True))
            elif (element.tag == '{%s}struct' % TP_NS):
                self.members.append(TpStruct(self, element)())
            elif (element.tag == '{%s}enum' % TP_NS):
                self.members.append(TpEnumeration(self, element)())
            elif (element.tag == '{%s}flags' % TP_NS):
                self.members.append(TpFlags(self, element)())

        self.dump()

    def dump(self):
        if self.flags & NO_IDL == 0:
            self.dump_idl()
        if self.flags & NO_SOURCE == 0:
            self.dump_source()

    def dump_idl(self):
        sub_interfaces      = []
        interface_items     = []
        interface_includes  = []
        interface_forwards  = []

        for member in self.members:
            sub_interfaces.extend(member.sub_interfaces)
            interface_items.extend(member.interface_items)
            interface_includes.extend(member.interface_includes)
            interface_forwards.extend(member.interface_forwards)

        output = []

        # IDL includes.
        output.append("#include \"nsISupports.idl\"")
        includes = make_unique(interface_includes)
        for include in includes:
            output.append("#include \"%s\"" % include)
        output.append("\n")
 
        # IDL forward declarations.
        interface_forwards.append("%{C++")
        interface_forwards.append("#include \"glib/gtypes.h\"")
        interface_forwards.append("%}")
        interface_forwards.append("native gpointer(gpointer);\n")
        output.append("\n".join(interface_forwards))
        output.append("\n")
 
        # Sub interfaces
        output.append("\n".join(sub_interfaces))
        output.append("\n")
 
        if self.flags & NO_DEFAULT == 0:
            # Interface header (uuid etc)
            output.append("[scriptable, uuid(%s)]" % str(get_uuid(self.interface_name)))
            output.append("interface %s : nsISupports" % self.interface_name)
            output.append("{")
           
            # Interface members
            output.append("\n".join(interface_items))
           
            # Interface footer
            output.append("};")

        # Dump the IDL.
        filename = IDL_PATH + self.interface_name + ".idl"
        with open(filename, 'w') as f:
            f.write(license())
            f.write('\n'.join(output))

        XPIDL_SOURCES.append(self.interface_name + ".idl")


    def dump_source(self):
        implementation     = []   # The generated C++ source
        private_items      = []   # Class members by access scope
        protected_items    = []
        public_items       = []
        header_includes    = []   # Includes that go at the beginning of header
        header_forwards    = []   # Forward declaration that go in the header

        header = []
        output = []

        for member in self.members:
            implementation.extend(member.implementation)
            private_items.extend(member.private_items)
            protected_items.extend(member.protected_items)
            public_items.extend(member.public_items)
            header_includes.extend(member.header_includes)
            header_forwards.extend(member.header_forwards)

        # Includes.
        header.append("#include \"nsISupports.h\"")
        header.append("#include \"%s.h\"" % self.interface_name)
        header.append("#include \"glib.h\"")
        output.append("#include \"%s.h\"" % self.class_name)
        output.append("#include \"nsComponentManagerUtils.h\"")
        output.append("#include \"nsMemory.h\"")
        output.append("#include \"telepathy-glib/util.h\"")
        output.append("#include \"telepathy-glib/enums.h\"")
        output.append("#include \"telepathy-glib/gtypes.h\"")
        output.append("#include \"csTelepathyUtils.h\"")
        output.append("#include \"csTpGenericTypes.h\"")
        includes = cross_includes(self.class_name)
        for include in includes:
            output.append("#include \"%s\"" % include)

        header_includes.append("nsCOMPtr.h")
        header_includes.append("nsIMutableArray.h")
        header_includes.append("nsArrayUtils.h")
        if not self.flags & NO_DEFAULT:
            header_includes.append("csTpBaseProxies.h")
            header_includes.extend(telepathy_includes(self.name))
        includes = make_unique(header_includes)
        for include in includes:
            header.append("#include \"%s\"" % include)
        header.append("\n")

        # IDL forward declarations.
        header.append("\n".join(header_forwards))
        header.append("\n")
 
        if self.flags & NO_DEFAULT == 0:
            header.append("class %s: public %s, public virtual %s" % (self.class_name, self.interface_name, get_baseclass(self.name)))
            header.append("{")
            header.append("public:")
            header.append("  NS_DECL_%s" % self.interface_name.upper())
            header.append("")
            header.append("  %s();" % self.class_name)
            header.append("")
            header.append("\n".join(public_items))
            header.append("")
            header.append("protected:")
            header.append("\n".join(protected_items))
            header.append("")
            header.append("  ~%s();" % self.class_name)
            header.append("")
            header.append("private:")
            header.append("\n".join(private_items))
            header.append("};")

            implementation.append("")
            implementation.append("%s::%s()" % (self.class_name, self.class_name))
            implementation.append("{}")
            implementation.append("")
            implementation.append("%s::~%s()" % (self.class_name, self.class_name))
            implementation.append("{}")
            implementation.append("")
            
        # Implementation
        output.append("\n".join(implementation))

        # Dump the files.
        filename = CPP_PATH + self.class_name + ".cpp"
        with open(filename, 'w') as f:
            f.write(license())
            f.write('\n'.join(output))

        filename = CPP_PATH + self.class_name + ".h"
        with open(filename, 'w') as f:
            f.write(license())
            f.write("#ifndef __CS_TELEPATHY_HEADER_%s__\n" % self.name.upper())
            f.write("#define __CS_TELEPATHY_HEADER_%s__\n" % self.name.upper())
            f.write('\n')
            f.write('\n'.join(header))
            f.write('\n')
            f.write("#endif")
        
        CPP_SOURCES.append(self.class_name + ".cpp")


if __name__ == '__main__':
    argv = sys.argv[1:]

    if not os.path.exists(IDL_PATH):
        os.makedirs(IDL_PATH)

    if not os.path.exists(CPP_PATH):
        os.makedirs(CPP_PATH)

    root = etree.parse(argv[0])
    
    try:
        cache_file = open("uuid.cache", "r+b")
        UUID_CACHE = pickle.load(cache_file)
    except IOError:
        cache_file = open("uuid.cache", "w")
        UUID_CACHE = {}
    except EOFError:
        UUID_CACHE = {}

    gentypes = root.find("{%s}generic-types" % TP_NS)
    if gentypes is not None:
        TpInterface("GenericTypes", gentypes, NO_DEFAULT)()

    for node in root.findall("//node"):
        rootname = node.attrib["name"].replace("/", "").replace("_", "")
        interface = node.find("interface")
        TpInterface(rootname, interface, 0)()

    pickle.dump(UUID_CACHE, cache_file)
    cache_file.close()

    with open(CPP_PATH + "cppsrcs.mk", 'w') as f:
        f.write('CPPSRCS = \\\n\t')
        f.write(' \\\n\t'.join(CPP_SOURCES))
        f.write(' \\\n\t$(NULL)')

    with open(IDL_PATH + "xpidlsrcs.mk", 'w') as f:
        f.write('XPIDLSRCS = \\\n\t')
        f.write(' \\\n\t'.join(XPIDL_SOURCES))
        f.write(' \\\n\t$(NULL)')
        
    # Post process
    os.system('sed -i "s/d_bus/dbus/g" %s/%scsTpChannelTypeDBusTube.cpp' % (os.getcwd(), CPP_PATH))

