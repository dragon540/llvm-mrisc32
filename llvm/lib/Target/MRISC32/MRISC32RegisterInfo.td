//===----------------------------------------------------------===//
//  Declaration that defines the MRISC32 Register file
//===----------------------------------------------------------===//

class MRISC32Reg<bits<5> Enc, string n> : Register<n> {
    let HWEncoding{4-0} = Enc;
    let Namespace  = "MRISC32";
}

foreach I = 0-31 in {
    let isConstant = !eq(0, I) in
        def r#I : MRISC32Reg<I, "r"#I>;
}

class MRISC32RegisterClass<list<ValueType> types, int size, int alignment,
                            dag regList, int copycost = 1>
                           : RegisterClass<"MRISC32", types, alignment, regList> {

        let Size = size;
        let CopyCost = copycost;
}

def GPR       : MRISC32RegisterClass<[i32, f32], 32, 32, (add (sequence "r%u", 0, 31))>;
// Only consists of registers which can be used as destination register to store some values.
def GPRDst    : MRISC32RegisterClass<[i32, f32], 31, 31, (add (sequence "r%u", 1, 31))>;
