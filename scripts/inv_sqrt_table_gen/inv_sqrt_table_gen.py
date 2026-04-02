#!/usr/bin/env python3

import sys
from math import sqrt

#--------
class Blank:
    pass

def psconcat(*args):
    return str().join([str(arg) for arg in args])

def lsconcat(lst):
    #return str().join([str(elem) for elem in lst])
    return psconcat(*lst)

def fprintout(file, *args, flush=False):
    print(psconcat(*args), sep="", end="", file=file, flush=flush)

def printout(*args):
    fprintout(sys.stdout, *args)

def printerr(*args):
    fprintout(sys.stderr, *args)

def convert_enum_to_str(to_conv):
    return str(to_conv)[str(to_conv).find(".") + 1:]

def convert_str_to_enum_opt(to_conv, EnumT, STR_ENUM_MAP):
    if not (isinstance(to_conv, EnumT) or isinstance(to_conv, str)):
        raise TypeError(psconcat("convert_str_to_enum_opt() error: ",
            to_conv, " ", type(to_conv)))

    if isinstance(to_conv, EnumT):
        return to_conv
    else: # if isinstance(to_conv, str):
        if to_conv not in STR_ENUM_MAP:
            raise KeyError(to_conv)
        return STR_ENUM_MAP[to_conv]

def obj_err_str(obj, i=None, lst=None):
    if i is None:
        return psconcat("{!r}, {}".format(obj, type(obj)))
    else: # if i is not None:
        assert isinstance(i, int), \
            obj_err_str(i)
        assert lst is None or isinstance(lst, list), \
            obj_err_str(lst)

        if lst is None:
            return psconcat("{}, {!r}, {}".format(i, obj, type(obj)))
        else: # if isinstance(lst, list):
            return psconcat("{!r}, {}".format(lst, obj_err_str
                (obj, i, None)))
#--------
class NameDict:
    #--------
    def __init__(self, dct={}):
        self.__dct = dct
    #--------
    def dct(self):
        return self.__dct
    #--------
    def __getattr__(self, key):
        return self[key]
    def __getitem__(self, key):
        if NameDict.key_goes_in_dct(key):
            return self.__dct[key]
        else: # if not NameDict.key_goes_in_dct(key)
            return self.__dict__[key]

    def __setattr__(self, key, val):
        self[key] = val
    def __setitem__(self, key, val):
        if NameDict.key_goes_in_dct(key):
            self.__dct[key] = val
        else: # if not NameDict.key_goes_in_dct(key)
            self.__dict__[key] = val

    def __iadd__(self, val):
        if not (isinstance(val, list) or isinstance(val, tuple)):
            raise TypeError("`val`: type must be `list` or `tuple`: {}"
                .format(obj_err_str(val)))

        if isinstance(val, list):
            for item in val:
                if not isinstance(item, tuple):
                    raise TypeError("`item`: type must be `tuple`: {}"
                        .format(obj_err_str(item)))
                if not (len(item) == 2):
                    raise ValueError("`item`: `len` must be 2: {}"
                        .format(obj_err_str(item)))
                self[item[0]] = item[1]
        else: # if isinstance(val, tuple):
            if len(val) != 2:
                raise ValueError("`item`: `len` must be 2: {}"
                    .format(len(val)))
            self[val[0]] = val[1]
    #--------
    @staticmethod
    def key_goes_in_dct(key):
        return isinstance(key, str) \
            and (len(key) > 0) \
            and key[0].isalpha()
    #--------
#--------
def get_ls_mask(
    hi: int,
    lo: int,
):
    shift = min(hi, lo)
    ls_mask = (((1 << (abs(hi - lo) + 1)) - 1) << shift, shift)
    return ls_mask
def get_bits(
    obj: int,
    hi: int,
    lo: int,
):
    ls_mask = get_ls_mask(
        hi=hi,
        lo=lo,
    )
    return (obj & ls_mask[0]) >> ls_mask[1]
def set_bits(
    obj: int,
    hi: int,
    lo: int,
    val: int,
):
    ls_mask = get_ls_mask(
        hi=hi,
        lo=lo,
    )
    ret = obj & ~ls_mask[0]
    ret |= (val & (ls_mask[0] >> ls_mask[1])) << ls_mask[1]
    return ret
#--------

if __name__ == "__main__":
    assert(len(sys.argv) == 4)
    print(sys.argv)
    iw = int(sys.argv[1])
    fw = int(sys.argv[2])
    sz = int(sys.argv[3])
    assert(
        (sz >= 0)
        and (sz <= (1 << 16))
    )
    with open("InvSqrtLut.hpp", "w", encoding="utf-8") as f:
        my_fixed_t = "FixedPt(int{}_t, {})".format(iw, fw)

        f.write(
            "#include \"../../src_pipelinec/FixedPt.hpp\"\n"
            + "DO_TYPEDEF_FIXEDPT(int{}_t, {})\n".format(iw, fw)
            + "static {} inv_sqrt_lut[{}] = "
            .format(my_fixed_t, sz)
            + "{\n"
        )
        for i in range(sz):
            f.write(
                "\t({})".format(my_fixed_t)
                + "{.data="
                + "{}".format(
                    hex(int((1.0 / sqrt(float(i))) * float(1 << fw)))
                    if i > 0
                    else 0
                )
                + "},\n"

            )
        f.write(
            "};"
        )
        f.flush()
        #f.write(
        #)
