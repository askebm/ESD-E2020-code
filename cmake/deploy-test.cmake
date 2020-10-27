function(add_deploy_target ARG1)
	get_target_property(cDIR ${ARG1} BINARY_DIR)
	get_target_property(cNAME ${ARG1} NAME)
	add_custom_target(deploy_${cNAME}
		WORKING_DIRECTORY ${cDIR}
		COMMAND sshpass -p ${ZYBO_PASSWORD} scp "${cNAME}"
		"${ZYBO_USER}@${ZYBO_IP}:${ZYBO_DEPLOY_DIR}"
		&& sshpass -p ${ZYBO_PASSWORD} ssh "${ZYBO_USER}@${ZYBO_IP}" "${ZYBO_DEPLOY_DIR}/${cNAME}"
	)
	add_dependencies(deploy_${cNAME} ${ARG1})
endfunction()

