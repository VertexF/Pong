set (CMAKE_C_STANDARD 99)
set (CMAKE_C_STANDARD_REQUIRED TRUE)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(SndFileChecks)

configure_file (src/config.h.cmake src/config.h)

configure_file (include/sndfile.h.in include/sndfile.h)

# Public libsndfile headers
set (sndfile_HDRS
    include/sndfile.hh
    ${CMAKE_CURRENT_BINARY_DIR}/include/sndfile.h
    )

add_library (SNDFILE STATIC
    src/sfconfig.h
    src/sfendian.h
    src/sf_unistd.h
    src/common.h
    src/common.c
    src/file_io.c
    src/command.c
    src/pcm.c
    src/ulaw.c
    src/alaw.c
    src/float32.c
    src/double64.c
    src/ima_adpcm.c
    src/ms_adpcm.c
    src/gsm610.c
    src/dwvw.c
    src/vox_adpcm.c
    src/interleave.c
    src/strings.c
    src/dither.c
    src/cart.c
    src/broadcast.c
    src/audio_detect.c
    src/ima_oki_adpcm.c
    src/ima_oki_adpcm.h
    src/alac.c
    src/chunk.c
    src/ogg.h
    src/ogg.c
    src/chanmap.h
    src/chanmap.c
    src/id3.c
    $<$<BOOL:${WIN32}>:src/windows.c>
    src/sndfile.c
    src/aiff.c
    src/au.c
    src/avr.c
    src/caf.c
    src/dwd.c
    src/flac.c
    src/g72x.c
    src/htk.c
    src/ircam.c
    src/macos.c
    src/mat4.c
    src/mat5.c
    src/nist.c
    src/paf.c
    src/pvf.c
    src/raw.c
    src/rx2.c
    src/sd2.c
    src/sds.c
    src/svx.c
    src/txw.c
    src/voc.c
    src/wve.c
    src/w64.c
    src/wavlike.h
    src/wavlike.c
    src/wav.c
    src/xi.c
    src/mpc2k.c
    src/rf64.c
    src/ogg_vorbis.c
    src/ogg_speex.c
    src/ogg_pcm.c
    src/ogg_opus.c
    src/ogg_vcomment.c
    src/nms_adpcm.c
    src/GSM610/config.h
    src/GSM610/gsm.h
    src/GSM610/gsm610_priv.h
    src/GSM610/add.c
    src/GSM610/code.c
    src/GSM610/decode.c
    src/GSM610/gsm_create.c
    src/GSM610/gsm_decode.c
    src/GSM610/gsm_destroy.c
    src/GSM610/gsm_encode.c
    src/GSM610/gsm_option.c
    src/GSM610/long_term.c
    src/GSM610/lpc.c
    src/GSM610/preprocess.c
    src/GSM610/rpe.c
    src/GSM610/short_term.c
    src/GSM610/table.c
    src/G72x/g72x.h
    src/G72x/g72x_priv.h
    src/G72x/g721.c
    src/G72x/g723_16.c
    src/G72x/g723_24.c
    src/G72x/g723_40.c
    src/G72x/g72x.c
    src/ALAC/ALACAudioTypes.h
    src/ALAC/ALACBitUtilities.h
    src/ALAC/EndianPortable.h
    src/ALAC/aglib.h
    src/ALAC/dplib.h
    src/ALAC/matrixlib.h
    src/ALAC/alac_codec.h
    src/ALAC/shift.h
    src/ALAC/ALACBitUtilities.c
    src/ALAC/ag_dec.c
    src/ALAC/ag_enc.c
    src/ALAC/dp_dec.c
    src/ALAC/dp_enc.c
    src/ALAC/matrix_dec.c
    src/ALAC/matrix_enc.c
    src/ALAC/alac_decoder.c
    src/ALAC/alac_encoder.c
    ${sndfile_HDRS}
    ${CMAKE_CURRENT_BINARY_DIR}/src/config.h
    )

target_include_directories (SNDFILE
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        src
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src>
    )

if(MSVC)
    set_property(TARGET SNDFILE PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
