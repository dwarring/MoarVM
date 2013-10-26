/* Bytecode annotation, post-resolution. */
struct MVMBytecodeAnnotation {
    MVMuint32 bytecode_offset;
    MVMuint32 filename_string_heap_index;
    MVMuint32 line_number;
};

void MVM_bytecode_unpack(MVMThreadContext *tc, MVMCompUnit *cu);
MVMBytecodeAnnotation * MVM_bytecode_resolve_annotation(MVMThreadContext *tc, MVMStaticFrameBody *sfb, MVMuint32 offset);
MVMBytecodeAnnotation * MVM_bytecode_get_annotation(MVMThreadContext *tc, MVMStaticFrameBody *sfb, MVMuint32 index);
