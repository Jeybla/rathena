ALTER TABLE `atcommandlog` MODIFY `atcommand_date` DATETIME DEFAULT NULL;
ALTER TABLE `branchlog` MODIFY `branch_date` DATETIME DEFAULT NULL;
ALTER TABLE `cashlog` MODIFY `time` DATETIME DEFAULT NULL;
ALTER TABLE `chatlog` MODIFY `time` DATETIME DEFAULT NULL;
ALTER TABLE `feedinglog` MODIFY `time` DATETIME DEFAULT NULL;
ALTER TABLE `loginlog` MODIFY `time` DATETIME DEFAULT NULL;
ALTER TABLE `mvplog` MODIFY `mvp_date` DATETIME DEFAULT NULL;
ALTER TABLE `npclog` MODIFY `npc_date` DATETIME DEFAULT NULL;
ALTER TABLE `picklog` MODIFY `time` DATETIME DEFAULT NULL;
ALTER TABLE `zenylog` MODIFY `time` DATETIME DEFAULT NULL;

